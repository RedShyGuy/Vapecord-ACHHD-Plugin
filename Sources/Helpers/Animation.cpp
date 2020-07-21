#include "cheats.hpp"
#include "Helpers/Animation.hpp"

namespace CTRPluginFramework
{ //336729B0, 769DC4

4d9da0(33672DB0, snake, 1)

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

		//Get Coordinates for animation	
		Process::Write32((u32)&pfunction02, 0x4A2488);
		pfunction02(animInstance + 0x8, (u32)GameHelper::GetCoordinates()); 
		
		//emotion change
		if(animID == 0x56) {
			Process::Write8(animInstance + 0x1C, emotion);
			Process::Write8(animInstance + 0x1D, 1);
		}
		//outfit change
		else if(animID == 0x42) {
			Process::Write8(animInstance + 0x1C, item);
			Process::Write8(animInstance + 0x20, emotion);
			Process::Write32(animInstance + 0x44, 0x02880000);
		}
		//hold item
		else if(animID == 0x43) {
			Process::Write16(animInstance + 0x1C, item & 0xFFFF);
			Process::Write16(animInstance + 0x1E, (item >> 0x10) & 0xFFFF);
			Process::Write8(animInstance + 0x20, 0x01);
		}
		//maybe snake???
		else if(animID == 0x0B) {
			//Writes Snake to animation
			Process::Write16(animInstance + 0x1C, snake & 0xFFF);
			//Writes Sound to animation
			Process::Write16(animInstance + 0x1E, sound & 0xFFFF);
			
			Process::Write8(animInstance + 0x22, 1);
			Process::Write16(animInstance + 0x24, 0xFFFE);
			Process::Write8(animInstance + 0x26, 4);
			Process::Write8(animInstance + 0x27, *(u8 *)(player + 0x2F));
		}
		//any other animation
		else {
			Process::Write8(animInstance + 0x1E, item);
		}
		
		//Execute standard Animation
		Animation::ExecuteAnimation(animID, animInstance);
	
		Sleep(Milliseconds(25));
		return 1;
	}
}