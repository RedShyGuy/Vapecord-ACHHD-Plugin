#include "cheats.hpp"

namespace CTRPluginFramework {
	void AppearanceUpdate() {
		u32 i = GameHelper::GetPInstance();
		if(i == 0)
			return;
		
		static const u32 APPEARANCE_DAT = Region::AutoRegion(0x4F02FC, 0x4F02C8, -1);
		static FUNCT func = FUNCT(APPEARANCE_DAT);
		func.Call<void>(i, 0);
	}
	
	void playerchange(MenuEntry *entry) {
		static bool speedmode = false;
		
		if(speedmode ? Controller::IsKeysDown(entry->Hotkeys[0].GetKeys()) : Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			static const u32 pData = GameHelper::GetPlayerData();
			
			Process::Write8(pData + 0xC, Utils::Random(0, 0x1F)); //Hair
			Process::Write8(pData + 0xD, Utils::Random(0, 7)); //Tan
			Process::Write8(pData + 0xE, Utils::Random(0, 0xF)); //Hair Color
			Process::Write8(pData + 0xF, Utils::Random(0, 0xC)); //Eyes
			Process::Write8(pData + 0x10, Utils::Random(0, 5)); //Eye Color
			
			Process::Write16(pData + 0x12, Utils::Random(0x266A, 0x273E)); //Headwear
			Process::Write16(pData + 0x16, Utils::Random(0x273F, 0x2794)); //Glasses
			Process::Write16(pData + 0x1A, Utils::Random(0x2324, 0x2566)); //Shirt
			Process::Write16(pData + 0x1E, Utils::Random(0x2567, 0x25E2)); //Pants
			Process::Write16(pData + 0x22, Utils::Random(0x25E3, 0x2606)); //Socks
			Process::Write16(pData + 0x26, Utils::Random(0x2607, 0x2644)); //Shoes
			//Process::Write16(pData + 0x2A, Utils::Random(0x3221, 0x3277)); //Tool
			
			AppearanceUpdate();
			Sleep(Milliseconds(150));
		}

		if(Controller::IsKeysPressed(entry->Hotkeys[1].GetKeys())) {
			speedmode = !speedmode;
			OSD::Notify("Speed Mode " << (speedmode ? (Color::Green << "ON") : (Color::Red << "OFF")));
		}
	}
}