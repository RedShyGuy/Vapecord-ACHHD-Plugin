#include "3ds.h"
#include "CTRPluginFramework.hpp"
#include "cheats.hpp"
#include <vector>

#define CONFIGNAME "plugin.bin"

namespace CTRPluginFramework
{	
	Color SaveCodes(0xFF0033FF);
	Color MovementCodes(0xFF0033FF);
	Color PlayerCodes(0xFF0033FF);
	Color AnimationCodes(0xFF0033FF);
	Color MiscCodes(0xFF0033FF);
	
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
		//settings.AllowSearchEngine = false;
		//settings.AllowActionReplay = false;
	    //settings.WaitTimeToBoot = Time(Seconds(30));
		//settings.MainTextColor = Color::DeepSkyBlue;
		settings.BackgroundMainColor = Color::Black;
		settings.BackgroundSecondaryColor = Color::Black;
		//settings.BackgroundBorderColor = Color::Blue; 
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
	
	int	main(void) {
		PluginMenu *menu = new PluginMenu("ACHHD Vapecord Public Plugin", 1, 0, 0, "Creator: Lukas#4444. \nSpecial thanks: Fussels  \nDiscord: https://discord.gg/w9nvqjW");
		menu->SynchronizeWithFrame(true);
		MenuFolder *A = nullptr, *B = nullptr, *C = nullptr, *D = nullptr, *E = nullptr;

		A = new MenuFolder(Color(SaveCodes) << "Save Codes");
		//A->Append(new MenuEntry(Color(PlayerCodes) << "Save Dumper" , nullptr, savedump, "Test.")),
		//A->Append(new MenuEntry(Color(PlayerCodes) << "Save Restore" , nullptr, saverestore, "Test.")),
		menu->Append(A);
		
		B = new MenuFolder(Color(MovementCodes) << "Movement Codes");
		B->Append(EntryWithHotkey(new MenuEntry(Color(MovementCodes) << "Walk Through Walls" , collisions, "Test"), Hotkey(Key::L | Key::DPadUp, Color(MovementCodes) << "Walk Over"))),
		B->Append(EntryWithHotkey(new MenuEntry(Color(MovementCodes) << "Room Warping" , roomwarp, "Test"), Hotkey(Key::R | Key::X, Color(MovementCodes) << "Room Warping"))),
		B->Append(EntryWithHotkey(new MenuEntry(Color(MovementCodes) << "Coordinate Modifier", coordmod, coordspeed, "Lets you move around your player."),{ Hotkey(Key::A, "Initial Button "), Hotkey(Key::DPadLeft, "Move Left "), Hotkey(Key::DPadRight, "Move Right "), Hotkey(Key::DPadUp, "Move Up "), Hotkey(Key::DPadDown, "Move Down ") })),
		menu->Append(B);

		C = new MenuFolder(Color(PlayerCodes) << "Player Codes");
		C->Append(new MenuEntry(Color(PlayerCodes) << "Player Changer" , nullptr, playerchange, "Test.")),
		menu->Append(C);

		D = new MenuFolder(Color(AnimationCodes) << "Animation Codes");
		D->Append(EntryWithHotkey(new MenuEntry(Color(SaveCodes) << "Set Animation", setanim, "Test."),{ Hotkey(Key::A | Key::DPadRight, "Set Mode"), Hotkey(Key::A | Key::DPadLeft, "Input ID"), Hotkey(Key::A | Key::B, "Execute Mode") })),
		D->Append(EntryWithHotkey(new MenuEntry(Color(AnimationCodes) << "Idle", idle, "Press the buttons to reset your animation."),{ Hotkey(Key::R, "Idle") })),
		menu->Append(D);
		
		E = new MenuFolder(Color(MiscCodes) << "Misc Codes");
		E->Append(new MenuEntry(Color(MiscCodes) << "Debug OSD", debug, "Test.")),
		E->Append(EntryWithHotkey(new MenuEntry(Color(MiscCodes) << "Execute Functions" , miscFunctions, "Test"), Hotkey(Key::Y | Key::DPadDown, Color(MiscCodes) << "Quick Menu"))),
		E->Append(new MenuEntry(Color(MiscCodes) << "Fast Game Speed", fastgamespeed, "Test.")),
		menu->Append(E);

		menu->Run();

		return 0;
	}
}