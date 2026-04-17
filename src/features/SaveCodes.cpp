#include "features/cheats.hpp"
#include "core/infrastructure/SaveBackupManager.hpp"
#include "core/infrastructure/Language.hpp"
#include "core/game_api/Game.hpp"
#include "core/Converters.hpp"
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

	void UnlockAllHappyHomeHandbookLessons(MenuEntry *entry) {
		if (MessageBox(Language::getInstance()->get(TextID::HANDBOOK_PROMPT), DialogType::DialogYesNo).SetClear(ClearScreen::Top)()) {
			TakumiData* data = Game::GetTakumiSaveData();
			if (data) {
				ACHHD_Data& achhdData = data->data;
				ACHHD_Player player = achhdData.player;

				player.flags.unkFlag77 = 1;
				player.flags.CustomDesignsUnlocked = 1;
				player.flags.EvenMoreDesignsUnlocked = 1;
				player.flags.WindowsAndMoreUnlocked = 1;
				player.flags.SoundSceneryUnlocked = 1;
				player.flags.RefurbishingUnlocked = 1;
				player.flags.HappyHomeCameraUnlocked = 1;
				player.flags.WorldInsectsUnlocked = 1;
				player.flags.WorldFishUnlocked = 1;
				player.flags.AncientFossilsUnlocked = 1;
				player.flags.GyroidsUnlocked = 1;
				player.flags.ArtCollectionUnlocked = 1;
				player.flags.StylingMachineUnlocked = 1;

				MessageBox(Language::getInstance()->get(TextID::HANDBOOK_SUCCESS)).SetClear(ClearScreen::Top)();
			} else {
				MessageBox(Language::getInstance()->get(TextID::SAVE_LOAD_FAIL)).SetClear(ClearScreen::Top)();
			}
		}
	}

	void NameEditor(MenuEntry *entry) {
		TakumiData* data = Game::GetTakumiSaveData();
		ACHHD_Player* player = Game::GetPlayerSaveData();
		if (!player) {
			MessageBox(Language::getInstance()->get(TextID::SAVE_LOAD_FAIL)).SetClear(ClearScreen::Top)();
			return;
		}

		Keyboard keyboard(Language::getInstance()->get(TextID::NAME_EDITOR_PROMPT));
		std::string input = "";
		keyboard.SetMaxLength(8);
		if (keyboard.Open(input, input) < 0) {
			return;
		}

		u32 Takumi = (u32)data;

		PlayerID oldPlayerID = player->playerInfo;
		Convert::STR_TO_U16(input, player->playerInfo.PlayerName);
		PlayerID newPlayerID = player->playerInfo;

		for(u32 addr = Takumi; addr < (Takumi + sizeof(TakumiData)); addr++) {
			if(*(PlayerID *)addr == oldPlayerID) {
				*(PlayerID *)addr = newPlayerID;
			}
		}

		MessageBox(Language::getInstance()->get(TextID::NAME_EDITOR_SUCCESS)).SetClear(ClearScreen::Top)();
	}

	void AppearanceEditor(MenuEntry *entry) {
		ACHHD_Player* player = Game::GetPlayerSaveData();
		if (!player) {
			MessageBox(Language::getInstance()->get(TextID::SAVE_LOAD_FAIL)).SetClear(ClearScreen::Top)();
			return;
		}

		Language *language = Language::getInstance();

		static const u8 ValidAppearanceID[5][2] = {
			{ 0x00, 0x1F }, { 0x00, 0x07 },
			{ 0x00, 0x0F }, { 0x00, 0x0C },
			{ 0x00, 0x05 }
		};

		const std::vector<std::string> playeropt = {
			language->get(TextID::VECTOR_PLAYER_MOD_HAIR_STYLE),
			language->get(TextID::VECTOR_PLAYER_MOD_TAN),
			language->get(TextID::VECTOR_PLAYER_MOD_HAIR_COLOR),
			language->get(TextID::VECTOR_PLAYER_MOD_EYE_STYLE),
			language->get(TextID::VECTOR_PLAYER_MOD_EYE_COLOR),
			language->get(TextID::VECTOR_PLAYER_MOD_GENDER),
		};

		const std::vector<std::string> genderopt = {
			language->get(TextID::VECTOR_PLAYER_MOD_GENDER_MALE),
			language->get(TextID::VECTOR_PLAYER_MOD_GENDER_FEMALE),
		};

		u8 value = 0;

		Keyboard optKb(language->get(TextID::KEY_PLAYER_MOD_CHOOSE_ACTION), playeropt);

		int choice = optKb.Open();
		if(choice < 0) {
			return;
		}

		switch(choice) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				optKb.GetMessage() = language->get(TextID::CHOOSE_VALUE);
				optKb.SetSlider(ValidAppearanceID[choice][0], ValidAppearanceID[choice][1]);
				if (optKb.Open(value) < 0) {
					return;
				}

				switch(choice) {
					case 0: player->features.HairStyle = value; break;
					case 1: player->features.Tan = value; break;
					case 2: player->features.HairColor= value; break;
					case 3: player->features.EyeStyle = value; break;
					case 4: player->features.EyeColor = value; break;
					default: return;
				}
			break;

			case 5: {
				optKb.Populate(genderopt);
				int gender = optKb.Open();
				if(gender < 0) {
					return;
				}

				//Player::EditGender(4, gender);
			} break;

			default:
				return;
		}

		Game::AppearanceUpdate();
	}

	void UnlockAllEmoticons(MenuEntry *entry) {

	}

	void UnlockAllFurniture(MenuEntry *entry) {

	}

	void UnlockAmiiboPhone(MenuEntry *entry) {
		
	}
}