#include "cheats.hpp"

namespace CTRPluginFramework
{
	void setanim(MenuEntry *entry) {
		static u8 AnimID = 0x03;
		static u8 EmoteID = 0x01;
		static u16 ItemID = 0x0001;
		static u16 SnakeID = 0x0001;
		static u16 SoundID = 0x0001;
		
		static int mode = 0;
		static int setmode = 0;

		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			switch(mode) {
				default: break;
				case 0:
					OSD::Notify("Animation Mode", Color::Red);
					mode++;
					setmode = 1;
				break;
				case 1:
					OSD::Notify("Emotion Mode", Color::Orange);
					mode++;
					setmode = 2;
				break;
				case 2:
					OSD::Notify("Item Mode", Color::Magenta);
					mode++;
					setmode = 3;
				break;
				case 3:
					OSD::Notify("Snake Mode", Color::Yellow);
					mode++;
					setmode = 4;
				break;
				case 4:
					OSD::Notify("Sound Mode", Color::Lime);
					mode = mode - 4;
					setmode = 5;
				break;
			}
		}
		
		if(Controller::IsKeysPressed(entry->Hotkeys[1].GetKeys())) {	
			switch(setmode) {
				case 0: return;
				case 1: {
					SetUpKB("Enter Animation ID:", true, 2, AnimID, AnimID);
				} break;
				case 2: {
					SetUpKB("Enter Emotion ID:", true, 2, EmoteID, EmoteID);
				} break;
				case 3: {
					SetUpKB("Enter Item ID:", true, 2, ItemID, ItemID);
				} break;
				case 4: {
					SetUpKB("Enter Snake ID:", true, 2, SnakeID, SnakeID);
				} break;
				case 5: {
					SetUpKB("Enter Sound ID:", true, 2, SoundID, SoundID);
				} break;
			}
		}
		
		if(Controller::IsKeysPressed(entry->Hotkeys[2].GetKeys())) {
			Animation::AnimationWrapper(AnimID, EmoteID, ItemID, SnakeID, SoundID);
		}
	}
	
	void idle(MenuEntry *entry) {
		if(entry->Hotkeys[0].IsDown()) {
			Animation::AnimationWrapper(3, 0, 0, 0, 0);
		}
	}
}