#include "cheats.hpp"

namespace CTRPluginFramework
{
	void playerchange(MenuEntry *entry) {
		static bool speedmode = false;
		
		if(speedmode ? Controller::IsKeysDown(entry->Hotkeys[0].GetKeys()) : Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			Animation::AnimationWrapper(0x42, 0, Utils::Random(0x266A, 0x273E), 0, 0);
			Animation::AnimationWrapper(0x42, 1, Utils::Random(0x273F, 0x2794), 0, 0);
			Animation::AnimationWrapper(0x42, 2, Utils::Random(0x2324, 0x2566), 0, 0);			
			Animation::AnimationWrapper(0x42, 3, Utils::Random(0x2567, 0x25E2), 0, 0); 
			Animation::AnimationWrapper(0x42, 4, Utils::Random(0x25E3, 0x2606), 0, 0);
			Animation::AnimationWrapper(0x42, 5, Utils::Random(0x2607, 0x2644), 0, 0);
			Animation::AnimationWrapper(3, 0, 0, 0, 0);
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
		/*0x33672DC8 = Hat
		0x33672DCC = Accessoire
		0x33672DD0 = Shirt
		0x33672DD4 = Trousers
		0x33672DD8 = Socks 739814
		0x33672DDC = Shoes*/
	}
}