#pragma once

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
    namespace SaveBackupManager {
        /*
        Backs up all save files from ARCHIVE_SAVEDATA to the Checkpoint folder on SD.
        Creates a subfolder named "<prefix> <timestamp>" (e.g. "Backup 2026-04-09 14h30").
        On success/partial, writes the folder name to backupFolderName.
        Returns true if all files were copied successfully.
        */
        bool BackupAllToCheckpoint(const std::string &prefix, std::string &backupFolderName);

        /*
        Backs up all save files using an exact folder name (no timestamp, no marker).
        */
        bool BackupAllToCheckpoint(const std::string &folderName);

        /*
        Returns the Checkpoint game folder path for the current title.
        */
        std::string GetGamePath(void);

        /*
        Lists all backup folders matching a given prefix inside the game path.
        */
        void ListBackups(const std::string &gamePath, const std::string &prefix, std::vector<std::string> &backups);

        /*
        Finds the oldest backup by .timestamp marker file.
        */
        std::string FindOldestBackup(const std::string &gamePath, const std::vector<std::string> &backups);

        /*
        Writes a .timestamp marker to a backup folder.
        */
        void WriteTimestamp(const std::string &path);

        /*
        Generates a backup folder name: "<prefix> <YYYY-MM-DD HHhMM>"
        */
        std::string MakeBackupName(const std::string &prefix);
    }
}
