#include "cheats.hpp"

namespace CTRPluginFramework
{
	//Made by Kominost!
	void collisions(MenuEntry *entry) {
		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			switch(*(u32 *)0x4DB0F8) {
				case 0xE3A09001:
					Process::Write32(0x4DB0F8, 0xE3A09000);
					OSD::Notify("Walk Over Things " << Color::Green << "ON");
				break;
				case 0xE3A09000:
					Process::Write32(0x4DB0F8, 0xE3A09001);
					OSD::Notify("Walk Over Things " << Color::Red << "OFF");
				break;
			}
		}
	}
	
	void RoomChange(Keyboard& keyboard, KeyboardEvent& event) {
		std::string input = keyboard.GetInput();
		keyboard.GetMessage() = GameHelper::GetStageName(input != "" ? std::stoi(input, nullptr, 16) : 0);
	}
	
	void roomwarp(MenuEntry *entry) {
		u8 room = 0;
		if(entry->Hotkeys[0].IsDown()) {
			Sleep(Seconds(0.1f));
			Keyboard kb("Type a Room ID.");
			kb.OnKeyboardEvent(RoomChange);
			if(kb.Open(room, room) != -1) {
				GameHelper::RoomChange(room);
			}
		}
	}
	
	float cspeed = 5.0;

	void coordspeed(MenuEntry *entry) {
		Keyboard kb("");
		kb.GetMessage() = "Enter speed:\n5 is default speed";
		kb.IsHexadecimal(false);
		kb.SetMaxLength(2);
		kb.Open(cspeed);
	}

	void coordmod(MenuEntry *entry) {
		if(entry->Hotkeys[0].IsDown()) {
			volatile float *pCoords = (float *)GameHelper::GetCoordinates();
			if(pCoords != nullptr) {
				if(entry->Hotkeys[1].IsDown()) 
					*pCoords -= cspeed;
				if(entry->Hotkeys[2].IsDown()) 
					*pCoords += cspeed;
				if(entry->Hotkeys[3].IsDown()) 
					*((float *)((vu32)pCoords + 8)) -= cspeed;
				if(entry->Hotkeys[4].IsDown()) 
					*((float *)((vu32)pCoords + 8)) += cspeed;
			}
		}
	}
}