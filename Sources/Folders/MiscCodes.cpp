#include "cheats.hpp"

namespace CTRPluginFramework
{
	bool debugOSD(const Screen &screen) {
		if(GameHelper::GetPInstance() == 0) 
			return 0;
		
		float X = *(float *)GameHelper::GetCoordinates(), Z = *(float *)(GameHelper::GetCoordinates() + 8);
		u32 wX = GameHelper::GetWorldCoords(), wY = GameHelper::GetWorldCoords() + 4;
		u32 ItemOffset = (u32)GameHelper::GetItemAtWorldCoords(*(u8 *)wX, *(u8 *)wY);
		
		if(screen.IsTop) {
			screen.Draw("Coordinates: " << std::to_string(X).erase(4) << "|" << std::to_string(Z).erase(4), 0, 0);
			screen.Draw(Utils::Format("World Coordinates: %02X|%02X", *(u8 *)wX, *(u8 *)wY), 0, 10);
			screen.Draw(Utils::Format("Room: %02X", *(u8 *)Code::ROOM_ID), 0, 20);
			screen.Draw(Utils::Format("Animation: %02X", Animation::GetCurrentAnim()), 0, 30);
			screen.Draw(Utils::Format("Emotion: %02X", Animation::GetCurrentEmotion()), 0, 40);
			screen.Draw(Utils::Format("Snake: %03X", Animation::GetCurrentSnake()), 0, 50);
			screen.Draw("Standing on: " << (ItemOffset != 0 ? Utils::Format("%08X", *(u32 *)ItemOffset) : "N/A"), 0, 60);
		}
		return 1;
	} 
	
	void debug(MenuEntry *entry) {
		if(entry->WasJustActivated()) 
			OSD::Run(debugOSD);
		else if(!entry->IsActivated()) 
			OSD::Stop(debugOSD);
	}
	
	void Dropper(MenuEntry *entry) {
		if(GameHelper::GetPInstance() == 0) 
			return;
		
		static u32 ItemID = 0x7FFE;
		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			SetUpKB("Enter Item ID", true, 8, ItemID, ItemID);
		}
		
		if(entry->Hotkeys[1].IsDown()) {
			if(*(u8 *)Code::ROOM_ID == 0x01) {
				u32 wX = GameHelper::GetWorldCoords(), wY = GameHelper::GetWorldCoords() + 4;
					
				GameHelper::DropItem(&ItemID, *(u32 *)wX, *(u32 *)wY);
			}
		}
	}

	static bool Turbo_Call = false;

	void FunctionsCaller(MenuEntry *entry) {
		static u32 funcaddress;
		static u32 p[11];
		u32 result;
		static int size;

        if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
            if(SetUpKB("Enter address of function:", true, 8, funcaddress, funcaddress)) {
				Keyboard KB("Enter ID:");
				KB.SetMaxLength(8);
				KB.IsHexadecimal(true);
				for(int i = 0; i < 12; i++) {
					Sleep(Milliseconds(100));
					KB.GetMessage() = "Enter value for param " << std::to_string(i) << ":" << 
					"\n" << Color::Blue << "0x11111111 for player instance" << 
					"\n" << Color::Red << "0x22222222 for animation instance" << 
					"\n" << Color::Green << "0x33333333 for map offset";
					
					if(KB.Open(p[i]) == -1) {
						size = i--;
						OSD::Notify(Utils::Format("Set Function: %08X with %02d parameters!" , funcaddress, size));
						return;
					}

					switch(p[i]) {
						case 0x11111111: 
							p[i] = GameHelper::GetPlayerOffset();
						break;

						case 0x22222222:
							p[i] = Animation::GetAnimationInstance();
						break;

						case 0x33333333:
							p[i] = GameHelper::GetCurrentMap();
						break;
					}
				}	
			}
        }

		if(Turbo_Call ? Controller::IsKeysDown(entry->Hotkeys[1].GetKeys()) : Controller::IsKeysPressed(entry->Hotkeys[1].GetKeys())) {
			if(!Process::CheckAddress(funcaddress))
				return;

			Sleep(Milliseconds(100));
			Process::Write32((u32)&FUN, funcaddress);
			switch(size) {
				case 0: result = FUN(); break;
				case 1: result = FUN(p[0]); break;
				case 2: result = FUN(p[0], p[1]); break;
				case 3: result = FUN(p[0], p[1], p[2]); break;
				case 4: result = FUN(p[0], p[1], p[2], p[3]); break;
				case 5: result = FUN(p[0], p[1], p[2], p[3], p[4]); break;
				case 6: result = FUN(p[0], p[1], p[2], p[3], p[4], p[5]); break;
				case 7: result = FUN(p[0], p[1], p[2], p[3], p[4], p[5], p[6]); break;
				case 8: result = FUN(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]); break;
				case 9: result = FUN(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]); break;
				case 10: result = FUN(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]); break;
				case 11: result = FUN(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]); break;
			}
			OSD::Notify(Utils::Format("Returned Value: %08X", result));
		}
    }

	void unlockshops(MenuEntry *entry) {
		u32 p = GameHelper::GetPlayerOffset();
		//Main Street
		//School = 	 p + 0x1B4D80
		//Hospital = p + 0x1B5EB8
		//Cafe = 	 p + 0x1B6FF0
		//Store = 	 p + 0x1B8128
		
		//Idk = 	 p + 0x1B9260
		//Idk =		 p + 0x1BA398
		
	}

	void fastgamespeed(MenuEntry *entry) { 	
		u32 FAST_GAME = Region::AutoRegion(0x44DAF4, -1, -1);
		if(entry->WasJustActivated()) 
			Process::Write32(FAST_GAME, 0xE3E004FF);

		else if(!entry->IsActivated()) 	
			Process::Write32(FAST_GAME, 0xE59400A0);
	}
}