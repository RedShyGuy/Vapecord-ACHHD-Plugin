#include "features/cheats.hpp"
#include "platform/ctrpf/MenuEntryIds.hpp"
#include "platform/ctrpf/UtilsExtras.hpp"
#include "core/infrastructure/Language.hpp"
#include "platform/ctrpf/Plugin_Color.hpp"
#include "platform/ctrpf/FolderTypes.hpp"
#include "platform/ctrpf/FolderTypeTextMap.hpp"
#include "Files.h"

#include <unordered_map>

namespace CTRPluginFramework {
	struct NamedHotkey {
		Hotkey hotkey;
		TextID nameKey;

		NamedHotkey(u32 keys, const TextID &nameKey)
			: hotkey(keys, UtilsExtras::setLanguageByKey(nameKey)), nameKey(nameKey)
		{
		}
	};

	struct FolderInfo {
		FolderType folderType;
		SubFolder subFolder;
		std::string customNote;
	};

	static std::unordered_map<MenuFolder *, FolderInfo> g_folderInfos;

	static std::string GetFolderName(FolderType type) {
		return Language::getInstance()->get(GetFolderTextId(type));
	}

	static std::string GetSubFolderName(FolderType parent, SubFolder sub) {
		return Language::getInstance()->get(GetSubFolderTextId(parent, sub));
	}

	static std::string GetFolderNote(FolderType type) {
		TextID noteKey = GetFolderNoteTextId(type);
		return noteKey != TextID::NONE ? Language::getInstance()->get(noteKey) : "";
	}

	static std::string GetSubFolderNote(FolderType parent, SubFolder sub) {
		TextID noteKey = GetSubFolderNoteTextId(parent, sub);
		return noteKey != TextID::NONE ? Language::getInstance()->get(noteKey) : "";
	}

	static std::string ResolveFolderNote(FolderType folderType, SubFolder subFolder, const std::string &customNote = "") {
		if (!customNote.empty())
			return customNote;

		return subFolder != SubFolder::None ? GetSubFolderNote(folderType, subFolder) : GetFolderNote(folderType);
	}

	static Color GetFolderColor(FolderType type) {
		if (type >= FolderType::Save && type <= FolderType::Misc) {
			if (CustomColorsExist()) {
				std::vector<ColorEntry> customColors = GetCustomColors();
				for (const ColorEntry& entry : customColors) {
					if (entry.folderType == type)
						return Color(entry.r, entry.g, entry.b);
				}
			}
		}

		for (const ColorEntry& entry : defaultColors) {
			if (entry.folderType == type)
				return Color(entry.r, entry.g, entry.b);
		}

		return Color::White;
	}

	static MenuFolder *CreateFolder(FolderType folderType, SubFolder subFolder = SubFolder::None, const std::string &note = "") {
		MenuFolder *folder = new MenuFolder(GetFolderColor(folderType) << (subFolder != SubFolder::None ? GetSubFolderName(folderType, subFolder) : GetFolderName(folderType)), ResolveFolderNote(folderType, subFolder, note));
		folder->SetColor(GetFolderColor(folderType));
		g_folderInfos[folder] = { folderType, subFolder, note };
		return folder;
	}

	bool TryGetFolderInfo(MenuFolder *folder, FolderType &folderType, SubFolder &subFolder) {
		auto it = g_folderInfos.find(folder);
		if (it == g_folderInfos.end())
			return false;

		folderType = it->second.folderType;
		subFolder = it->second.subFolder;
		return true;
	}

	static std::string ResolveTextByKey(u32 key) {
		return Language::getInstance()->get(static_cast<TextID>(key));
	}

	static MenuEntry *CreateEntry(const TextID &nameKey, void(*gameFunc)(MenuEntry*), void(*menuFunc)(MenuEntry*), const TextID &noteKey = TextID::NONE, unsigned int uuID = 0) {
		MenuEntry *entry = new MenuEntry(
			UtilsExtras::setLanguageByKey(nameKey),
			gameFunc,
			menuFunc,
			noteKey != TextID::NONE ? UtilsExtras::setLanguageByKey(noteKey) : "",
			uuID
		);

		entry->SetNameKey(static_cast<u32>(nameKey));
		entry->SetNoteKey(noteKey != TextID::NONE ? static_cast<u32>(noteKey) : 0);
		return entry;
	}

	static MenuEntry *CreateEntry(const TextID &nameKey, void(*gameFunc)(MenuEntry*), const TextID &noteKey = TextID::NONE, unsigned int uuID = 0) {
		MenuEntry *entry = new MenuEntry(
			UtilsExtras::setLanguageByKey(nameKey),
			gameFunc,
			noteKey != TextID::NONE ? UtilsExtras::setLanguageByKey(noteKey) : "",
			uuID
		);

		entry->SetNameKey(static_cast<u32>(nameKey));
		entry->SetNoteKey(noteKey != TextID::NONE ? static_cast<u32>(noteKey) : 0);
		return entry;
	}

	static MenuEntry *EntryWithHotkey(MenuEntry *entry, const std::vector<NamedHotkey> &hotkeys) {
        if(entry != nullptr) {
			for(const NamedHotkey &hotkey : hotkeys) {
				entry->Hotkeys += hotkey.hotkey;
				entry->AppendHotkeyNameKey(static_cast<u32>(hotkey.nameKey));
			}
        }
        return entry;
    }

	static MenuEntry *EntryWithHotkey(MenuEntry *entry, const NamedHotkey &hotkey) {
        if(entry != nullptr) {
			entry->Hotkeys += hotkey.hotkey;
			entry->AppendHotkeyNameKey(static_cast<u32>(hotkey.nameKey));
        }
        return entry;
    }

/*This will load all the folders and entrys*/
    void InitMenu(PluginMenu *menu) {
		MenuEntry::SetLocalizationCallback(ResolveTextByKey);
		PluginMenu::SetFolderRefreshCallback([](MenuFolder *folder) {
			auto it = g_folderInfos.find(folder);
			if (it == g_folderInfos.end())
				return;

			const FolderInfo &info = it->second;
			folder->SetColor(GetFolderColor(info.folderType));
			folder->SetName(GetFolderColor(info.folderType) << (info.subFolder != SubFolder::None ? GetSubFolderName(info.folderType, info.subFolder) : GetFolderName(info.folderType)));
			folder->Note() = ResolveFolderNote(info.folderType, info.subFolder, info.customNote);
		});
	/////////////////////
	/*Save Codes Folder*/
	/////////////////////
		MenuFolder *SAVEC = CreateFolder(FolderType::Save);
		SAVEC->Append(CreateEntry(TextID::SAVE_SETTINGS, nullptr, SaveSettings, TextID::SAVE_SETTINGS_NOTE, MenuEntryId::SaveBackupSettings));
		menu->Append(SAVEC);
		
	/////////////////////////
	/*Movement Codes Folder*/
	/////////////////////////
		MenuFolder *MOVEC = CreateFolder(FolderType::Movement);
		MOVEC->Append(EntryWithHotkey(CreateEntry(TextID::WALK_THROUGH_WALLS, collisions, TextID::WALK_THROUGH_WALLS_NOTE, MenuEntryId::MovementWalkThroughWalls), {
			NamedHotkey(Key::L | Key::DPadUp, TextID::HK_WALK_OVER)
		}));
		MOVEC->Append(EntryWithHotkey(CreateEntry(TextID::ROOM_WARPING, roomwarp, TextID::ROOM_WARPING_NOTE, MenuEntryId::MovementRoomWarping), {
			NamedHotkey(Key::R | Key::X, TextID::HK_ROOM_WARPING)
		}));
		MOVEC->Append(EntryWithHotkey(CreateEntry(TextID::COORDINATE_MODIFIER, coordmod, coordspeed, TextID::COORDINATE_MODIFIER_NOTE, MenuEntryId::MovementCoordMod), { 
			NamedHotkey(Key::A, TextID::HK_INITIAL_BUTTON), 
			NamedHotkey(Key::DPadLeft, TextID::HK_MOVE_LEFT), 
			NamedHotkey(Key::DPadRight, TextID::HK_MOVE_RIGHT), 
			NamedHotkey(Key::DPadUp, TextID::HK_MOVE_UP), 
			NamedHotkey(Key::DPadDown, TextID::HK_MOVE_DOWN) 
		}));
		menu->Append(MOVEC);

	///////////////////////
	/*Player Codes Folder*/
	///////////////////////
		MenuFolder *PLAYC = CreateFolder(FolderType::Player);
	////////////////////////////
	/*Player Save Codes Folder*/
	////////////////////////////
		MenuFolder *PSAVEC = CreateFolder(FolderType::Player, SubFolder::PlayerSave);
		PSAVEC->Append(EntryWithHotkey(CreateEntry(TextID::PLAYER_RANDOMIZER, playerchange, TextID::PLAYER_RANDOMIZER_NOTE, MenuEntryId::PlayerSaveRandomizer), { 
			NamedHotkey(Key::L | Key::DPadRight, TextID::HK_RANDOMIZE_OUTFIT), 
			NamedHotkey(Key::L | Key::DPadLeft, TextID::HK_SET_SPEED) 
		}));
		PLAYC->Append(PSAVEC);
		menu->Append(PLAYC);

	//////////////////////////
	/*Animation Codes Folder*/
	//////////////////////////
		MenuFolder *ANIMC = CreateFolder(FolderType::Animation);
		ANIMC->Append(EntryWithHotkey(CreateEntry(TextID::SET_ANIMATION, setanim, TextID::SET_ANIMATION_NOTE, MenuEntryId::AnimationSetAnimation), { 
			NamedHotkey(Key::A | Key::DPadRight, TextID::HK_SET_MODE), 
			NamedHotkey(Key::A | Key::DPadLeft, TextID::HK_INPUT_ID), 
			NamedHotkey(Key::A | Key::B, TextID::HK_EXECUTE_MODE) 
		}));
		ANIMC->Append(EntryWithHotkey(CreateEntry(TextID::IDLE_ANIMATION, idle, TextID::IDLE_ANIMATION_NOTE, MenuEntryId::AnimationIdleAnimation), {
			NamedHotkey(Key::R, TextID::HK_IDLE)
		}));
		//ANIMC->Append(new MenuEntry("NPC Code", NPCCode, "")),
		menu->Append(ANIMC);
		
	/////////////////////
	/*Misc Codes Folder*/
	/////////////////////
		MenuFolder *MISC = CreateFolder(FolderType::Misc);
		MISC->Append(CreateEntry(TextID::PLAYER_INFO, debug, TextID::PLAYER_INFO_NOTE, MenuEntryId::MiscPlayerInfo));
		MISC->Append(EntryWithHotkey(CreateEntry(TextID::INSTANT_DROP, Dropper, TextID::INSTANT_DROP_NOTE, MenuEntryId::MiscInstantDrop), { 
			NamedHotkey(Key::L | Key::DPadRight, TextID::HK_SELECT_ITEM_ID), 
			NamedHotkey(Key::L | Key::DPadDown, TextID::HK_DROP_ITEM) 
		}));
		MISC->Append(CreateEntry(TextID::FAST_GAME_SPEED, fastgamespeed, TextID::FAST_GAME_SPEED_NOTE, MenuEntryId::MiscFastGameSpeed));
		menu->Append(MISC);

	////////////////////
	/*Dev Codes Folder*/
	////////////////////
	#if DEVMODE
		MenuFolder *DEVC = CreateFolder(FolderType::Dev);
		DEVC->Append(EntryWithHotkey(CreateEntry(TextID::EXECUTE_FUNCTIONS, FunctionsCaller, TextID::EXECUTE_FUNCTIONS_NOTE, MenuEntryId::DevExecuteFunction), { 
			NamedHotkey(Key::L | Key::DPadRight, TextID::HK_INPUT_FUNCTION_DATA), 
			NamedHotkey(Key::L | Key::DPadDown, TextID::HK_CALL_FUNCTION) 
		}));
		menu->Append(DEVC);
	#endif

		menu->Append(CreateEntry(TextID::PLUGIN_SETTINGS, nullptr, pluginSettingsEntry, TextID::NONE, MenuEntryId::PluginSettings));
	}
}



