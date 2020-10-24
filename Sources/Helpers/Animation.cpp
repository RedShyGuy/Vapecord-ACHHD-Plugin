#include "cheats.hpp"
#include "Helpers/Animation.hpp"

namespace CTRPluginFramework
{ 
//336729B0, 769DC4
//33673E28, 
//3221 to 3277 tools 
//NPC Animation
	/*void Animation::SetNPCAnimation(u32 npc, u8 animID, u8 emotion, u16 snake) {
		if(animID == 0xC) {
			Process::Write32((u32)&pfunction03, 0x527E5C);
		}
		else if(animID == 0xE) {
			pfunction03(npc, 0, emotion);
			Process::Write32((u32)&pfunction05, 0x528FA0);
			pfunction05(npc, 0, snake, 0, 0);
		}
		else {
			u32 null[]{ 0 };
			Process::Write32((u32)&pfunction08, 0x525A24);
			pfunction08(npc, animID, 0, 0x85A534, (u32)null, (u32)null, 0, 0x66873C);
		}	
	}*/
//Get Current Animation	
	u8 Animation::GetCurrentAnim() {
		u32 player = GameHelper::GetPInstance();
		//If player is not loaded return
		if(player == 0)
			return 0;
		
		return(*(u8 *)(player + 0x710));
	}
//Get Current Snake	
	u16 Animation::GetCurrentSnake() {
		u32 player = GameHelper::GetPInstance();
		//If player is not loaded return
		if(player == 0)
			return 0;
		
		return(*(u8 *)(player + 0x4CA));
	}
//Get Current Emotion
	u8 Animation::GetCurrentEmotion() {
		u32 player = GameHelper::GetPInstance();
		//If player is not loaded return
		if(player == 0)
			return 0;
		
		return(*(u8 *)(player + 0x628));
	}
//Get Animation Instance
	u32 Animation::GetAnimationInstance() {
		u32 player = GameHelper::GetPInstance();
		//If player is not loaded return
		if(player == 0)
			return 0;
		//Return Animation Instance
		Process::Write32((u32)&pfunction01, 0x4DDE0C);
		return pfunction01(player);
	}
//Execute Animation	
	u32 Animation::ExecuteAnimation(u8 animID, u32 animInstance) {
		u32 player = GameHelper::GetPInstance();
		//If player is not loaded return
		if(player == 0)
			return 0;
		//If animation is not loaded return
		if(animInstance == 0)
			return 0;
		//Executes Animation
		Process::Write32((u32)&pfunction04, 0x4D8960);
		return pfunction04(player, animID, animInstance, 0);
	}
//Animation Wrapper
	bool Animation::AnimationWrapper(u8 animID, u8 emotion, u16 item, u16 snake, u16 sound) {
		//Get player data
		u32 player = GameHelper::GetPInstance();
		//If player is not loaded return
		if(player == 0)
			return 0;
		//Get Animation Data
		u32 animInstance;
		animInstance = Animation::GetAnimationInstance();
		//If animation data is 0 return
		if(animInstance == 0)
			return 0;

		//Get World Coords
		u32 wX = GameHelper::GetWorldCoords();
		u32 wY = GameHelper::GetWorldCoords() + 4;

		/*float coords[3];
		//Get Coordinates for animation
		Process::Write32((u32)&pfunction02, 0x4A2488);
		pfunction02(animInstance + 0x8, (u32)GameHelper::WorldCoordsToCoords(*(u8 *)wX, *(u8 *)wY, coords)); */

		//emotion change
		if(animID == 0x56) {
			Process::Write8(animInstance + 0x1C, emotion);
			Process::Write8(animInstance + 0x1D, 1);
		}
		//outfit change
		else if(animID == 0x42) {
			Process::Write32(animInstance + 0x1C, item);
			Process::Write8(animInstance + 0x20, emotion);
			Process::Write32(animInstance + 0x44, 0x02880000);
		}
		//hold item
		else if(animID == 0x43) {
			Process::Write16(animInstance + 0x1C, item & 0xFFFF);
			Process::Write16(animInstance + 0x1E, (item >> 0x10) & 0xFFFF);
			Process::Write8(animInstance + 0x20, 0x01);
		}
		//Snake :D
		else if(animID == 0x5A) {
			//Writes Snake to animation
			Process::Write16(animInstance + 0x1C, snake & 0xFFF);
			Process::Write16(animInstance + 0x1E, snake & 0xFFFF);
			
			Process::Write8(animInstance + 0x20, *(u8 *)(player + 0x6B));
			Process::Write8(animInstance + 0x21, 1);
			Process::Write8(animInstance + 0x22, 5);
		}
		//pick amiibo phone
		else if(animID == 0x18 | animID == 0x12) {
			Process::Write32(animInstance + 0x1C, *(u32 *)GameHelper::GetCoordinates());
			Process::Write32(animInstance + 0x20, *(u32 *)(GameHelper::GetCoordinates() + 4));
			Process::Write32(animInstance + 0x24, *(u32 *)(GameHelper::GetCoordinates() + 8));
			Process::Write16(animInstance + 0x28, 0x8258);
		}
		else if(animID == 0x44) {
			//this makes the player coords not change after the animation
			Process::Write8(animInstance + 0x20, 1);
			Process::Write8(animInstance + 0x21, 1);
		}
		//Sit down
		else if(animID == 0x2D | animID == 0x2E) {	
			Process::Write32(animInstance + 0x20, *(u32 *)GameHelper::GetCoordinates());
			Process::Write32(animInstance + 0x24, *(u32 *)(GameHelper::GetCoordinates() + 4));
			Process::Write32(animInstance + 0x28, *(u32 *)(GameHelper::GetCoordinates() + 8));
			Process::Write8(animInstance + 0x1C, 2);
		}
		
		//any other animation
		else {
			Process::Write8(animInstance + 0x1C, *(u8 *)wX);		
			Process::Write8(animInstance + 0x1D, *(u8 *)wY);
		}
		 
		//Execute standard Animation
		Animation::ExecuteAnimation(animID, animInstance);
	
		Sleep(Milliseconds(25));
		return 1;
	}
}