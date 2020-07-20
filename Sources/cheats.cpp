#include "cheats.hpp"
#include "MenuEntryhelpers.hpp"
#include "text_color.h"
#include "ctrulib/util/utf.h"
#include "CTRPluginFramework/System/Rect.hpp"
#include "OSDMenu.hpp"
#include "GameHelper.hpp"

#define READU32(x)      *(u32 *)(x)
#define READU16(x)      *(u16 *)(x)
#define READU8(x)       *(u8 *)(x)
#define READFLOAT(x)    *(float *)(x)

#define WRITEU8(a, v)   *(u8 *)(a) = (u8)v
#define WRITEU16(a, v)  *(u16 *)(a) = (u16)v
#define WRITEU32(a, v)  *(u32 *)(a) = (u32)v 
#define WRITEU64(a, v)  *(u64 *)(a) = (u64)v

#define ADD32(a, v)     *(u32 *)a += v
#define SUB32(a, v)     *(u32 *)a -= v
#define ADD64(a, v)     *(vs64 *)a += v
#define SUB64(a, v)     *(vs64 *)a -= v
#define ADD16(a, v)     *(u16 *)a += v
#define SUB16(a, v)     *(u16 *)a -= v
#define ADD8(a, v)      *(u8 *)a += v
#define SUB8(a, v)      *(u8 *)a -= v
#define ADDTOFLOAT(a, v)  *((float*)(a)) += (float)v
#define SUBTOFLOAT(a, v)  *((float*)(a)) -= (float)v

namespace CTRPluginFramework
{
	volatile u32(*pfunction00)();
	volatile u32(*pfunction01)(u32 param1);
	volatile u32(*pfunction02)(u32 param1, u32 param2);
	volatile u32(*pfunction03)(u32 param1, u32 param2, u32 param3);
	volatile u32(*pfunction04)(u32 param1, u32 param2, u32 param3, u32 param4);
	volatile u32(*pfunction05)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
	volatile u32(*pfunction06)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
	volatile u32(*pfunction07)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
	volatile u32(*pfunction08)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
	volatile u32(*pfunction09)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9);
	volatile u32(*pfunction010)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10);
	volatile u32(*pfunction011)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10, u32 param11);

	File * file = new File();
	
	Keyboard *kb = new Keyboard("Enter ID:");
	Keyboard *optKb = new Keyboard("Choose option:");
	Keyboard *playKb = new Keyboard("Select your Player");
	Keyboard *customkb = new Keyboard("Set your custom dump offset\nHow to: \n1.Type in the start offset to dump from\n2.Type in the length of the dump\n3. Type in the file type the dump should have\n- Great to test things.\n- If you don't know what you are doing don't\n- restore weird dumps!.");
	Keyboard *customkb1 = new Keyboard("Now you can dump the file/or restore it\n(the restore function also needs the same start offset/dump length and file type as the dump!).");
	Keyboard *musickb = new Keyboard("Change the sound speed of the music.");
	Keyboard *nookkb = new Keyboard("Choose an upgrade for your shop.");
	Keyboard *randkb = new Keyboard("Lets you randomize your Player.");
	Keyboard *wearkb = new Keyboard("What do you want to wear?");

	std::vector<std::string> cmnOpt{
		"Enable",
		"Disable"
	};

	void playerchange(MenuEntry *entry) {
		/*0x33672DC8 = Hat
		0x33672DCC = Accessoire
		0x33672DD0 = Shirt
		0x33672DD4 = Trousers
		0x33672DD8 = Socks
		0x33672DDC = Shoes*/
	}
	//0496D4C    sub_496CAC+A0   496F5C
	bool debugOSD(const Screen &screen) {	
		u8 room = *(u8 *)0x738CE9;
		u8 anim = GameHelper::GetCurrentAnim();
		if (screen.IsTop) {
			screen.Draw("Room: " << Hex(room), 0, 0);
			screen.Draw("Animation: " << Hex(anim), 0, 10);
		}
	} 
	
	void debug(MenuEntry *entry) {
		if (entry->WasJustActivated()) OSD::Run(debugOSD);
		else if (!entry->IsActivated()) OSD::Stop(debugOSD);
	}

	void roomwarp(MenuEntry *entry) {
		static u8 room = 0;
		if (entry->Hotkeys[0].IsDown()) {
			(Seconds(0.1f));
			Keyboard kb("Type a Room ID.");
			if (kb.Open(room, room) != -1) {
				GameHelper::RoomChange(room);
			}
		}
	}

	void idle(MenuEntry *entry) {
		if (entry->Hotkeys[0].IsDown()) {
			GameHelper::ExecuteAnimation(0x03);
		}
	}
	
	void setanim(MenuEntry *entry) {
		static u8 animID = 0;
		static u8 animkey = 0;
		if (entry->Hotkeys[0].IsDown()) {
			Sleep(Seconds(0.1f));
			Keyboard animation("Type an Animation ID.");
			if (animation.Open(animkey, animkey) != -1) {
				animkey = animID;
			}
		}
		if (entry->Hotkeys[1].IsDown()) {
			GameHelper::ExecuteAnimation(animkey);
		}
	}

	float cspeed = 5.0;

	void coordspeed(MenuEntry *entry) {
		kb->GetMessage() = "Enter speed:\n5 is default speed";
		kb->IsHexadecimal(false);
		kb->SetMaxLength(2);
		kb->Open(cspeed);
	}

	void coordmod(MenuEntry *entry) {
		if (entry->Hotkeys[0].IsDown()) {
			if (GameHelper::GetCoordinates() != 0) {
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
	
	void fastgamespeed(MenuEntry *entry) { 
		Entry::Write32(entry, 0x44DAF4, 0xE3E004FF, 0xE59400A0); 
	}

	/*void emotionmenu(MenuEntry *entry) { 
		Process::Write32(0x326A8CBC, 0x01020304);
		Process::Write32(0x326A8CC0, 0x05060708);
		Process::Write32(0x326A8CC4, 0x090A0B0C);
		Process::Write32(0x326A8CC8, 0x0D0E1011);
		Process::Write32(0x326A8CCC, 0x12131415);
		Process::Write32(0x326A8CD0, 0x16171819);
		Process::Write32(0x326A8CD4, 0x1A1B1C1D);
		Process::Write32(0x326A8CD8, 0x1E202124);
		Process::Write32(0x326A8CDC, 0x26272829);
		Process::Write32(0x326A8CE0, 0x2A2B2C2E);
		Process::Write32(0x326A8CE4, 0x2F303132);
		Process::Write32(0x326A8CE8, );
	}*/

	void miscFunctions(MenuEntry *entry) {	
		if (entry->Hotkeys[0].IsDown()) {
			s8 val;
			static u32 lastExecuted;
			u32 player, targetPlayer, animInstance, x, y;
			u32 param[11], res;
			if (SetUpKB("Enter address of function:", true, 8, lastExecuted, lastExecuted)) {
					u8 val;
					if (SetUpKB("Enter parameter count (max 11):", false, 2, val, 0)) {
						val = val % 12;
						kb->SetMaxLength(8);
						kb->IsHexadecimal(true);
						for (int i = 0; i < val; i++) {
							Sleep(Milliseconds(100));
							kb->GetMessage() = "Enter value for param " << std::to_string(i) << ":\n(0xABCDEF for current player instance)";
							if (kb->Open(param[i]) != 0) return;
						}
						Sleep(Milliseconds(100));
						switch (val) {
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

	bool SetUpKB(const std::string &msg, bool hex, const int length, u64 &output, u64 def, OnInputChange cb) {
		Sleep(Milliseconds(100));
		kb->GetMessage() = msg;
		kb->IsHexadecimal(hex);
		kb->SetMaxLength(length);
		kb->OnInputChange(cb);
		return kb->Open(output, def) == 0;
	}

	bool SetUpKB(const std::string &msg, bool hex, const int length, u32 &output, u32 def, OnInputChange cb) {
		Sleep(Milliseconds(100));
		kb->GetMessage() = msg;
		kb->IsHexadecimal(hex);
		kb->SetMaxLength(length);
		kb->OnInputChange(cb);
		return kb->Open(output, def) == 0;
	}

	bool SetUpKB(const std::string &msg, bool hex, const int length, u16 &output, u16 def, OnInputChange cb) {
		Sleep(Milliseconds(100));
		kb->GetMessage() = msg;
		kb->IsHexadecimal(hex);
		kb->SetMaxLength(length);
		kb->OnInputChange(cb);
		return kb->Open(output, def) == 0;
	}

	bool SetUpKB(const std::string &msg, bool hex, const int length, u8 &output, u8 def, OnInputChange cb) {
		Sleep(Milliseconds(100));
		kb->GetMessage() = msg;
		kb->IsHexadecimal(hex);
		kb->SetMaxLength(length);
		kb->OnInputChange(cb);
		return kb->Open(output, def) == 0;
	}
}