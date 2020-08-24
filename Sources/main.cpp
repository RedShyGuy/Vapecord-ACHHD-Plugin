#include "3ds.h"
#include "CTRPluginFramework.hpp"
#include "cheats.hpp"
#include <vector>

namespace CTRPluginFramework
{	
	static MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey) {
        if (entry != nullptr) {
            entry->Hotkeys += hotkey;
            entry->SetArg(new std::string(entry->Name()));
            entry->Name() += " " + hotkey.ToString();
            entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry *entry, int index) {
                std::string *name = reinterpret_cast<std::string *>(entry->GetArg());

                entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
            });
        }
        return (entry);
    }

    static MenuEntry *EntryWithHotkey(MenuEntry *entry, const std::vector<Hotkey> &hotkeys) {
        if (entry != nullptr) {
            for (const Hotkey &hotkey : hotkeys)
                entry->Hotkeys += hotkey;
        }
        return (entry);
    }
	
	void PatchProcess(FwkSettings &settings) {
		//OPTIONS
		settings.ThreadPriority = 0x30;
		settings.BackgroundMainColor = Color::Black;
		settings.BackgroundSecondaryColor = Color::Black;
		settings.WindowTitleColor = Color::Yellow;
		settings.MenuSelectedItemColor = Color::Lime;
		settings.MenuUnselectedItemColor = Color::White;
		settings.Keyboard.Background = Color::Black;
		settings.Keyboard.KeyBackground = Color::Black;
		settings.Keyboard.KeyBackgroundPressed = Color::Silver;
		settings.Keyboard.KeyText = Color::Lime;
		settings.Keyboard.KeyTextPressed = Color::Lime;
		settings.Keyboard.Cursor = Color::Lime;
		settings.Keyboard.Input = Color::Lime;
		settings.CustomKeyboard.BackgroundMain = Color::Black;
		settings.CustomKeyboard.BackgroundSecondary = Color::Black;
		settings.CustomKeyboard.BackgroundBorder = Color::Silver;
		settings.CustomKeyboard.KeyBackground = Color::Black;
		settings.CustomKeyboard.KeyBackgroundPressed = Color::Silver;
		settings.CustomKeyboard.KeyText = Color::Lime;
		settings.CustomKeyboard.KeyTextPressed = Color::Lime;
		settings.CustomKeyboard.ScrollBarBackground = Color::Black;
		settings.CustomKeyboard.ScrollBarThumb = Color::Black;
	}
	
	void ToolFix(void) {
		//this here gives the umbrella 0x3277 the correct data and lets the player use it correctly
		u32 i = GameHelper::GetPInstance();
		if(i == 0)
			return;
		
		u16 currentTool = *(u16 *)(i + 0x7A4);
		
		//tool unequip
		if(currentTool != 0x7FFE && Controller::IsKeyPressed(Key::DPadDown) && Animation::GetCurrentAnim() == 3) {
			Animation::AnimationWrapper(0x44, 0, 0, 0, 0);
		}
		//If tool is umbrella and player spins it
		if(currentTool == 0x3277 && Controller::IsKeyPressed(Key::A) && Animation::GetCurrentAnim() == 3) {
			Animation::AnimationWrapper(0x5F, 0, 0, 0, 0);
		}
		//if tool is popper, player can pop it
		if(currentTool == 0x3247 && Controller::IsKeyPressed(Key::A) && Animation::GetCurrentAnim() == 3) {
			Animation::AnimationWrapper(0x60, 0, 0, 0, 0);
		}
	}
	
	//very neccessary lol 
	void UmbrellaSecretEquip(void) {
		u8 room = *(u8 *)0x738CE9;
		if(room != 0x0A)
			return;
		
		u32 i = GameHelper::GetPInstance();
		if(i == 0)
			return;
		
		u16 currentTool = *(u16 *)(i + 0x7A4);
		if(currentTool != 0x7FFE)
			return;
		
		u32 wX = GameHelper::GetWorldCoords();
		u32 wY = GameHelper::GetWorldCoords() + 4;
		if(*(u8 *)wX != 0x0F)
			return;
		if(*(u8 *)wY != 0x0C)
			return;
		
		if(!Controller::IsKeyPressed(Key::A))
			return;
		
		if(Animation::GetCurrentAnim() != 0x48)
			return;
		
		Animation::AnimationWrapper(0x43, 0, 0x3277, 0, 0);
	}
	
	Color SaveCodes(0xFF0033FF);
	Color MovementCodes(0xFF0033FF);
	Color PlayerCodes(0xFF0033FF);
	Color AnimationCodes(0xFF0033FF);
	Color MiscCodes(0xFF0033FF);
	
	int	main(void) {
		PluginMenu *menu = new PluginMenu("ACHHD Vapecord Public Plugin", 1, 0, 0, "Creator: Lukas#4444.\nThanks to Kominost for the Walk Over Things! \nSpecial thanks: Fussels  \nDiscord: https://discord.gg/w9nvqjW");
		menu->SynchronizeWithFrame(true);
		menu->Callback(ToolFix);
		menu->Callback(UmbrellaSecretEquip);
		MenuFolder *SAVECODES = nullptr, *MOVECODES = nullptr, *PLAYERCODES = nullptr, *ANIMCODES = nullptr, *MISCCODES = nullptr;

		SAVECODES = new MenuFolder(Color(SaveCodes) << "Save Codes");
		SAVECODES->Append(new MenuEntry(Color(PlayerCodes) << "Save Settings" , nullptr, SaveSettings, "Lets you dump or restore your TAKUMI save")),
		menu->Append(SAVECODES);
		
		MOVECODES = new MenuFolder(Color(MovementCodes) << "Movement Codes");
		MOVECODES->Append(EntryWithHotkey(new MenuEntry(Color(MovementCodes) << "Walk Through Walls" , collisions, "Lets you walk over things"), Hotkey(Key::L | Key::DPadUp, "Walk Over"))),
		MOVECODES->Append(EntryWithHotkey(new MenuEntry(Color(MovementCodes) << "Room Warping" , roomwarp, "Lets you warp to other rooms"), Hotkey(Key::R | Key::X, "Room Warping"))),
		MOVECODES->Append(EntryWithHotkey(new MenuEntry(Color(MovementCodes) << "Coordinate Modifier", coordmod, coordspeed, "Lets you move around your player."),{ Hotkey(Key::A, "Initial Button "), Hotkey(Key::DPadLeft, "Move Left "), Hotkey(Key::DPadRight, "Move Right "), Hotkey(Key::DPadUp, "Move Up "), Hotkey(Key::DPadDown, "Move Down ") })),
		menu->Append(MOVECODES);

		PLAYERCODES = new MenuFolder(Color(PlayerCodes) << "Player Codes");
		PLAYERCODES->Append(EntryWithHotkey(new MenuEntry(Color(PlayerCodes) << "Outfit Randomizer", playerchange, "Lets you randomize your players outfit."), { Hotkey(Key::L | Key::DPadRight, "Randomize Outfit"), Hotkey(Key::L |Key::DPadLeft, "Set Speed") } )),
		menu->Append(PLAYERCODES);

		ANIMCODES = new MenuFolder(Color(AnimationCodes) << "Animation Codes");
		ANIMCODES->Append(EntryWithHotkey(new MenuEntry(Color(AnimationCodes) << "Set Animation", setanim, "Lets you set different types of animation."),{ Hotkey(Key::A | Key::DPadRight, "Set Mode"), Hotkey(Key::A | Key::DPadLeft, "Input ID"), Hotkey(Key::A | Key::B, "Execute Mode") })),
		ANIMCODES->Append(EntryWithHotkey(new MenuEntry(Color(AnimationCodes) << "Idle", idle, "Lets you reset your animation."),{ Hotkey(Key::R, "Idle") })),
		//ANIMCODES->Append(new MenuEntry(Color(AnimationCodes) << "NPC Code", NPCCode, "")),
		menu->Append(ANIMCODES);
		
		MISCCODES = new MenuFolder(Color(MiscCodes) << "Misc Codes");
		MISCCODES->Append(new MenuEntry(Color(MiscCodes) << "Debug OSD", debug, "Shows you usefull informations.")),
		//Not for the release neccessary
	  //MISCCODES->Append(EntryWithHotkey(new MenuEntry(Color(MiscCodes) << "Execute Functions" , miscFunctions, "Lets you execute functions"), Hotkey(Key::Y | Key::DPadDown, Color(MiscCodes) << "Quick Menu"))),
		MISCCODES->Append(new MenuEntry(Color(MiscCodes) << "Fast Game Speed", fastgamespeed, "Speeds up your game.")),
		menu->Append(MISCCODES);

		menu->Run();

		return 0;
	}
}//