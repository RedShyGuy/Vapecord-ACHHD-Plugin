#include "features/cheats.hpp"
#include "core/infrastructure/SaveBackupManager.hpp"
#include "core/infrastructure/Language.hpp"

#define SAVESIZE 0x2BE930

namespace CTRPluginFramework {
	void SaveSettings(MenuEntry *entry) {
		const Language *lang = Language::getInstance();

		const std::vector<std::string> options = {
			lang->get(TextID::SAVE_DUMPER),
			lang->get(TextID::SAVE_RESTORE),
			lang->get(TextID::FILE_DELETE),
		};

		Keyboard KB(lang->get(TextID::KEY_CHOOSE_BACKUP_ACTION), options);

		switch(KB.Open()) {
			default: break;
			case 0: {
				if (!MessageBox(lang->get(TextID::SAVE_BACKUP_UNSAVED_CHANGES), DialogType::DialogYesNo).SetClear(ClearScreen::Top)()) {
					break;
				}

				Keyboard nameKB(lang->get(TextID::SAVE_DUMPER_DUMP));
				std::string folderName;
				if (nameKB.Open(folderName) < 0 || folderName.empty()) {
					break;
				}

				if (SaveBackupManager::BackupAllToCheckpoint(folderName)) {
					MessageBox(Utils::Format(lang->get(TextID::SAVE_BACKUP_SUCCESS).c_str(), folderName.c_str())).SetClear(ClearScreen::Top)();
				}
				else {
					MessageBox(lang->get(TextID::SAVE_BACKUP_FAIL)).SetClear(ClearScreen::Top)();
				}
			} break;
			case 1: {
				MessageBox(lang->get(TextID::SAVE_RESTORE_CHECKPOINT)).SetClear(ClearScreen::Top)();
			} break;
			case 2: {
				std::string gamePath = SaveBackupManager::GetGamePath();
				std::vector<std::string> delBackups;
				SaveBackupManager::ListBackups(gamePath, "", delBackups);
				if (delBackups.empty()) {
					MessageBox(lang->get(TextID::SAVE_DELETE_NON_FOUND)).SetClear(ClearScreen::Top)();
					break;
				}

				Keyboard delKB(lang->get(TextID::FILE_DELETE), delBackups);
				int delChoice = delKB.Open();
				if (delChoice < 0) {
					break;
				}

				if (!MessageBox(Utils::Format(lang->get(TextID::SAVE_DELETE_CONFIRM).c_str(), delBackups[delChoice].c_str()), DialogType::DialogYesNo).SetClear(ClearScreen::Top)()) {
					break;
				}

				std::string delPath = SaveBackupManager::GetGamePath() + "/" + delBackups[delChoice];
				if (Directory::Remove(delPath) == 0) {
					MessageBox(Utils::Format(lang->get(TextID::SAVE_DELETE_SUCCESS).c_str(), delBackups[delChoice].c_str())).SetClear(ClearScreen::Top)();
				}
				else {
					MessageBox(lang->get(TextID::SAVE_DELETE_FAIL)).SetClear(ClearScreen::Top)();
				}
			} break;
		}
	}
}