#include "cheats.hpp"

namespace CTRPluginFramework
{
	void setanim(MenuEntry *entry) {
		static u8 AnimID = 0x03;
		static u8 EmoteID = 0x01;
		static u16 ItemID = 0x0001;
		static u16 SnakeID = 0x0001;
		
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
					mode = mode - 3;
					setmode = 4;
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
			}
		}
		
		if(Controller::IsKeysPressed(entry->Hotkeys[2].GetKeys())) {
			switch(setmode) {
				case 0: return;
				case 1: {
					Animation::AnimationWrapper(AnimID > 0x64 ? 3 : AnimID, EmoteID, ItemID, SnakeID, SoundID);
				} break;
				case 2: {
					Animation::AnimationWrapper(0x56, EmoteID, 0, 0, 0);
				} break;
				case 3: {
					Animation::AnimationWrapper(0x43, 0, ItemID, 0, 0);
				} break;
				case 4: {
					Animation::AnimationWrapper(0x5A, 0, 0, SnakeID, 0);
				} break;
			}
		}
	}
	
	void idle(MenuEntry *entry) {
		if(entry->Hotkeys[0].IsDown()) {
			Animation::AnimationWrapper(3, 0, 0, 0, 0);
		}
	}
	
	/*void NPCCode(MenuEntry *entry) {
		static u8 animID = 0;
		static u8 emotionID = 0;
		static u16 snakeID = 0;
		static u32 NPCOffset = 0;
		static int mode = 0;
		
		std::vector<std::string> npcOpt{
			"Set Animation",
			"Set Snake",
			"Set Emotion",
		};
		
		u32 i = GameHelper::GetPInstance();
		if(Controller::IsKeysPressed(Key::B + Key::DPadRight)) {
			switch(mode) {
				default: break;
				case 0:
					OSD::Notify("Lyle", Color::Blue);
					mode++;
					NPCOffset = i + 0x1C5AC;
				break;
				case 1:
					OSD::Notify("Isabelle", Color::Yellow);
					mode++;
					NPCOffset = i + 0x11C04;
				break;
				case 2:
					OSD::Notify("Lottie", Color::Magenta);
					mode = mode - 2;
					NPCOffset = i + 0x134A4;
				break;
			}
		}
		
		if(Controller::IsKeysPressed(Key::B + Key::DPadLeft)) {
			Keyboard npcmenu("");
			npcmenu.Populate(npcOpt);
			switch(npcmenu.Open()) {
				default: break;
				case 0: {
					SetUpKB("Enter Animation ID:", true, 2, animID, animID);
				} break;
				case 1: {
					SetUpKB("Enter Emotion ID:", true, 2, emotionID, emotionID);
				} break;
				case 2: {
					SetUpKB("Enter Snake ID:", true, 2, snakeID, snakeID);
				} break;
			}
		}
		
		if(Controller::IsKeyPressed(Key::R)) {
			if(NPCOffset == 0)
				return;
			
			Animation::SetNPCAnimation(NPCOffset, animID, emotionID, snakeID);
		}
	}*/
}