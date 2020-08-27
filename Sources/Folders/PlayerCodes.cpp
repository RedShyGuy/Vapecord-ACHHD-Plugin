#include "cheats.hpp"

namespace CTRPluginFramework
{
	void AppearanceUpdate() {
		u32 i = GameHelper::GetPInstance();
		if(i == 0)
			return;
		
		Process::Write32((u32)&pfunction02, 0x4F02FC);
		pfunction02(i, 0);
	}
	
	void playerchange(MenuEntry *entry) {
		static bool speedmode = false;
		
		if(speedmode ? Controller::IsKeysDown(entry->Hotkeys[0].GetKeys()) : Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			/*Animation::AnimationWrapper(0x42, 0, Utils::Random(0x266A, 0x273E), 0, 0);
			Animation::AnimationWrapper(0x42, 1, Utils::Random(0x273F, 0x2794), 0, 0);
			Animation::AnimationWrapper(0x42, 2, Utils::Random(0x2324, 0x2566), 0, 0);			
			Animation::AnimationWrapper(0x42, 3, Utils::Random(0x2567, 0x25E2), 0, 0); 
			Animation::AnimationWrapper(0x42, 4, Utils::Random(0x25E3, 0x2606), 0, 0);
			Animation::AnimationWrapper(0x42, 5, Utils::Random(0x2607, 0x2644), 0, 0);
			Animation::AnimationWrapper(3, 0, 0, 0, 0);*/
			u32 pData = GameHelper::GetPlayerData();
			
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
			if(!speedmode) {
				speedmode = true;
				OSD::Notify("Speed Mode " << Color::Green << "ON");
			}
			
			else {
				speedmode = false;
				OSD::Notify("Speed Mode " << Color::Red << "OFF");
			}
		}
	}
}