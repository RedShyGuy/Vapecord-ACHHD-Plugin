#include "core/infrastructure/SaveBackupManager.hpp"
#include <CTRPluginFramework.hpp>
#include "Files.h"
#include <3ds.h>
#include <cstring>
#include <ctime>
#include <vector>
#include <string>

namespace CTRPluginFramework {
    namespace SaveBackupManager {
        namespace {
            struct SaveFileInfo {
                std::string name;
                u64 size;
            };

            bool OpenSaveArchive(FS_Archive &archive) {
                FS_Path archivePath = fsMakePath(PATH_EMPTY, "");
                return R_SUCCEEDED(FSUSER_OpenArchive(&archive, ARCHIVE_SAVEDATA, archivePath));
            }

            bool ListSaveFiles(FS_Archive archive, std::vector<SaveFileInfo> &files) {
                Handle dirHandle;
                FS_Path dirPath = fsMakePath(PATH_ASCII, "/");
                if (R_FAILED(FSUSER_OpenDirectory(&dirHandle, archive, dirPath))) {
                    return false;
                }

                FS_DirectoryEntry entries[16];
                u32 entriesRead = 0;
                do {
                    if (R_FAILED(FSDIR_Read(dirHandle, &entriesRead, 16, entries))) {
                        break;
                    }
                        
                    for (u32 i = 0; i < entriesRead; ++i) {
                        if (entries[i].attributes & FS_ATTRIBUTE_DIRECTORY) {
                            continue;
                        }

                        std::string name;
                        Utils::ConvertUTF16ToUTF8(name, reinterpret_cast<const char16_t *>(entries[i].name));
                        files.push_back({ name, entries[i].fileSize });
                    }
                } while (entriesRead > 0);

                FSDIR_Close(dirHandle);
                return !files.empty();
            }

            bool CopySaveFileToSD(FS_Archive saveArchive, const SaveFileInfo &info, const std::string &destPath) {
                Handle srcHandle;
                std::string srcPath = "/" + info.name;
                FS_Path fsFilePath = fsMakePath(PATH_ASCII, srcPath.c_str());
                if (R_FAILED(FSUSER_OpenFile(&srcHandle, saveArchive, fsFilePath, FS_OPEN_READ, 0))) {
                    return false;
                }

                std::string fullDest = destPath + "/" + info.name;
                File destFile;
                int res = File::Open(destFile, fullDest, File::RWC | File::TRUNCATE);
                if (res != 0) {
                    FSFILE_Close(srcHandle);
                    return false;
                }

                constexpr u32 CHUNK_SIZE = 0x8000;
                u8 *buffer = new u8[CHUNK_SIZE];
                u64 offset = 0;
                u64 remaining = info.size;
                bool success = true;

                while (remaining > 0) {
                    u32 toRead = remaining > CHUNK_SIZE ? CHUNK_SIZE : static_cast<u32>(remaining);
                    u32 bytesRead = 0;
                    if (R_FAILED(FSFILE_Read(srcHandle, &bytesRead, offset, buffer, toRead)) || bytesRead == 0) {
                        success = false;
                        break;
                    }
                    if (destFile.Write(buffer, bytesRead) != 0) {
                        success = false;
                        break;
                    }
                    offset += bytesRead;
                    remaining -= bytesRead;
                }

                delete[] buffer;
                destFile.Flush();
                destFile.Close();
                FSFILE_Close(srcHandle);
                return success;
            }

            std::string GetCheckpointGameFolder() {
                u64 titleId = Process::GetTitleID();
                u32 uniqueId = static_cast<u32>((titleId >> 8) & 0xFFFFF);
                std::string hexPrefix = Utils::Format("0x%05X", uniqueId);
                Directory checkpointDir;

                if (Directory::Open(checkpointDir, "E:/3ds/Checkpoint/saves") == 0) {
                    std::vector<std::string> dirs;
                    checkpointDir.ListDirectories(dirs);
                    checkpointDir.Close();

                    for (const std::string &dir : dirs) {
                        if (dir.compare(0, hexPrefix.size(), hexPrefix) == 0) {
                            return dir;
                        }
                    }
                }

                return hexPrefix + " Happy Home Designer";
            }

            void EnsureCheckpointDirs() {
                Directory::Create("E:/3ds");
                Directory::Create("E:/3ds/Checkpoint");
                Directory::Create("E:/3ds/Checkpoint/saves");
            }
        }

        std::string GetGamePath(void) {
            EnsureCheckpointDirs();
            std::string gameFolderName = GetCheckpointGameFolder();
            std::string gamePath = Utils::Format(PATH_AUTOBACKUP, gameFolderName.c_str());
            Directory::Create(gamePath);
            return gamePath;
        }

        std::string MakeBackupName(const std::string &prefix) {
            time_t now = time(nullptr);
            struct tm *t = localtime(&now);
            char buf[32];
            strftime(buf, sizeof(buf), "%Y-%m-%d %Hh%M", t);
            return Utils::Format("%s %s", prefix.c_str(), buf);
        }

        void ListBackups(const std::string &gamePath, const std::string &prefix, std::vector<std::string> &backups) {
            Directory gameDir;
            if (Directory::Open(gameDir, gamePath) != 0) {
                return;
            }

            std::vector<std::string> dirs;
            gameDir.ListDirectories(dirs);
            gameDir.Close();

            for (const std::string &dir : dirs) {
                if (dir.compare(0, prefix.size(), prefix) == 0) {
                    backups.push_back(dir);
                }
            }
        }

        std::string FindOldestBackup(const std::string &gamePath, const std::vector<std::string> &backups) {
            u64 oldestTime = UINT64_MAX;
            std::string oldest = backups[0];
            for (const std::string &backup : backups) {
                std::string markerPath = gamePath + "/" + backup + "/.timestamp";
                File marker;
                if (File::Open(marker, markerPath, File::READ) != 0) {
                    return backup;
                }

                u64 timestamp = 0;
                marker.Read(&timestamp, sizeof(timestamp));
                marker.Close();
                if (timestamp < oldestTime) {
                    oldestTime = timestamp;
                    oldest = backup;
                }
            }
            return oldest;
        }

        void WriteTimestamp(const std::string &path) {
            std::string markerPath = path + "/.timestamp";
            File marker;
            if (File::Open(marker, markerPath, File::RWC | File::TRUNCATE) == 0) {
                u64 timestamp = osGetTime();
                marker.Write(&timestamp, sizeof(timestamp));
                marker.Flush();
                marker.Close();
            }
        }

        bool BackupAllToCheckpoint(const std::string &prefix, std::string &backupFolderName) {
            FS_Archive saveArchive;
            if (!OpenSaveArchive(saveArchive)) {
                return false;
            }

            std::vector<SaveFileInfo> files;
            if (!ListSaveFiles(saveArchive, files)) {
                FSUSER_CloseArchive(saveArchive);
                return false;
            }

            std::string gamePath = GetGamePath();
            backupFolderName = MakeBackupName(prefix);
            std::string targetPath = gamePath + "/" + backupFolderName;
            Directory::Create(targetPath);
            bool allSuccess = true;

            for (const SaveFileInfo &info : files) {
                if (!CopySaveFileToSD(saveArchive, info, targetPath)) {
                    allSuccess = false;
                }
            }

            WriteTimestamp(targetPath);
            FSUSER_CloseArchive(saveArchive);
            return allSuccess;
        }

        bool BackupAllToCheckpoint(const std::string &folderName) {
            FS_Archive saveArchive;
            if (!OpenSaveArchive(saveArchive)) {
                return false;
            }

            std::vector<SaveFileInfo> files;
            if (!ListSaveFiles(saveArchive, files)) {
                FSUSER_CloseArchive(saveArchive);
                return false;
            }

            std::string gamePath = GetGamePath();
            std::string targetPath = gamePath + "/" + folderName;
            Directory::Create(targetPath);
            bool allSuccess = true;

            for (const SaveFileInfo &info : files) {
                if (!CopySaveFileToSD(saveArchive, info, targetPath)) {
                    allSuccess = false;
                }
            }

            FSUSER_CloseArchive(saveArchive);
            return allSuccess;
        }
    }
}