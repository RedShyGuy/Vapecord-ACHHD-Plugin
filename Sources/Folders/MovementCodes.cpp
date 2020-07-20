#include "cheats.hpp"

namespace CTRPluginFramework
{
	//Made by Kominost!
	void collisions(MenuEntry *entry) {
		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			switch(*(u32 *)0x4DB0F8) {
				case 0xE3A09001:
					Process::Write32(0x4DB0F8, 0xE3A09000);
					OSD::Notify("Walk Over Things" << Color::Green << "ON");
				break;
				case 0xE3A09000:
					Process::Write32(0x4DB0F8, 0xE3A09001);
					OSD::Notify("Walk Over Things" << Color::Red << "OFF");
				break;
			}
		}
	}
	
	void roomwarp(MenuEntry *entry) {
		u8 room = 0;
		if(entry->Hotkeys[0].IsDown()) {
			Sleep(Seconds(0.1f));
			Keyboard kb("Type a Room ID.");
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
			if(GameHelper::GetCoordinates() != 0) {
				if(GameHelper::Outside()) {
					if (entry->Hotkeys[1].IsDown()) SUB32(0x33673410, cspeed); //DPadLeft
					if (entry->Hotkeys[2].IsDown()) ADD32(0x33673410, cspeed); //DpadRight
					if (entry->Hotkeys[3].IsDown()) SUB32(0x33673408, cspeed); //DpadUp
					if (entry->Hotkeys[4].IsDown()) ADD32(0x33673408, cspeed); //DpadDown
				}
				else {
					if (entry->Hotkeys[1].IsDown()) SUB32(0x33672A08, cspeed); //DPadLeft
					if (entry->Hotkeys[2].IsDown()) ADD32(0x33672A08, cspeed); //DpadRight
					if (entry->Hotkeys[3].IsDown()) SUB32(0x33672A00, cspeed); //DpadUp
					if (entry->Hotkeys[4].IsDown()) ADD32(0x33672A00, cspeed); //DpadDown
				}
			}
		}
	}
}