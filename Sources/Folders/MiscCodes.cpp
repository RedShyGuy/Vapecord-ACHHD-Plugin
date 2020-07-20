#include "cheats.hpp"

namespace CTRPluginFramework
{
	//0496D4C    sub_496CAC+A0   496F5C
	bool debugOSD(const Screen &screen) {	
		if(screen.IsTop) {
			screen.Draw("Room: " << Hex(*(u8 *)0x738CE9), 0, 0);
			screen.Draw("Animation: " << Hex(Animation::GetCurrentAnim()), 0, 10);
			screen.Draw("Snake: " << Hex(Animation::GetCurrentSnake()), 0, 20);
		}
		return 1;
	} 
	
	void debug(MenuEntry *entry) {
		if(entry->WasJustActivated()) 
			OSD::Run(debugOSD);
		else if(!entry->IsActivated()) 
			OSD::Stop(debugOSD);
	}
	//Made by Nico
	void miscFunctions(MenuEntry *entry) {	
		if(entry->Hotkeys[0].IsDown()) {
			s8 val;
			static u32 lastExecuted;
			u32 player, targetPlayer, animInstance, x, y;
			u32 param[11], res;
			Keyboard kb("");
			if(SetUpKB("Enter address of function:", true, 8, lastExecuted, lastExecuted)) {
				u8 val;
				if(SetUpKB("Enter parameter count (max 11):", false, 2, val, 0)) {
					val = val % 12;
					kb.SetMaxLength(8);
					kb.IsHexadecimal(true);
					for(int i = 0; i < val; i++) {
						Sleep(Milliseconds(100));
						kb.GetMessage() = "Enter value for param " << std::to_string(i) << ":\n(0xABCDEF for current player instance)";
						if(kb.Open(param[i]) != 0) 
							return;
					}
					Sleep(Milliseconds(100));
					switch(val) {
						case 0:
							Process::Write32((u32)&pfunction00, lastExecuted);
							res = pfunction00();
							break;
						case 1:
							Process::Write32((u32)&pfunction01, lastExecuted);
							res = pfunction01(param[0]);
							break;
						case 2:
							Process::Write32((u32)&pfunction02, lastExecuted);
							res = pfunction02(param[0], param[1]);
							break;
						case 3:
							Process::Write32((u32)&pfunction03, lastExecuted);
							res = pfunction03(param[0], param[1], param[2]);
							break;
						case 4:
							Process::Write32((u32)&pfunction04, lastExecuted);
							res = pfunction04(param[0], param[1], param[2], param[3]);
							break;
						case 5:
							Process::Write32((u32)&pfunction05, lastExecuted);
							res = pfunction05(param[0], param[1], param[2], param[3], param[4]);
							break;
						case 6:
							Process::Write32((u32)&pfunction06, lastExecuted);
							res = pfunction06(param[0], param[1], param[2], param[3], param[4], param[5]);
							break;
						case 7:
							Process::Write32((u32)&pfunction07, lastExecuted);
							res = pfunction07(param[0], param[1], param[2], param[3], param[4], param[5], param[6]);
							break;
						case 8:
							Process::Write32((u32)&pfunction08, lastExecuted);
							res = pfunction08(param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7]);
							break;
						case 9:
							Process::Write32((u32)&pfunction09, lastExecuted);
							res = pfunction09(param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7], param[8]);
							break;
						case 10:
							Process::Write32((u32)&pfunction010, lastExecuted);
							res = pfunction010(param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7], param[8], param[9]);
							break;
						case 11:
							Process::Write32((u32)&pfunction011, lastExecuted);
							res = pfunction011(param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7], param[8], param[9], param[10]);
							break;
						default:
							return;
					}
					OSD::Notify("Returned value: " << Hex(res));
				}
			}
		}	
	}
	
	void fastgamespeed(MenuEntry *entry) { 
		if(entry->WasJustActivated()) 
			Process::Write32(0x44DAF4, 0xE3E004FF);
		else if(!entry->IsActivated()) 	
			Process::Write32(0x44DAF4, 0xE59400A0);
	}
}