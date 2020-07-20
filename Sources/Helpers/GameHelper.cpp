#include "cheats.hpp"
#include "GameHelper.hpp"

namespace CTRPluginFramework
{
	const u64 USA = 0x000400000014F100; 
	const u64 EUR = 0x000400000014F200;
	const u64 JPN = 0x000400000014F000;
//Auto Region	
	int Region::AutoRegion(u32 usa, u32 eur, u32 jpn) {
		switch(Process::GetTitleID()) {
			default: return(usa);
			case USA: return(usa);
			case EUR: return(eur);
			case JPN: return(jpn);
		}
	}
//Get Coords
	float *GameHelper::GetCoordinates() {
		u32 i = GameHelper::GetPInstance();
		if(i != 0) 
			i += 0x50;
		
		return(float *)i;
	}
//If outside	
	bool GameHelper::Outside() {
		if(*(u32 *)0x33672A00 != 0) return true;
		else return false;
	}
//Call Room Change Function	
	u32 GameHelper::RoomChange(u8 room) {
		Process::Write32((u32)&pfunction04, 0x496F5C);
		return pfunction04(room, 1, 1, 0);
	}
//Get Player Instance	
	u32 GameHelper::GetPInstance() {
		Process::Write32((u32)&pfunction02, 0x49DA08);
		return pfunction02(0, 1);
	}
//Get Current Animation	
	u8 GameHelper::GetCurrentAnim() {
		if(Outside()) return *(u8 *)0x33673AC8;
		else return *(u8 *)0x336730C0;
	}
	bool GameHelper::GetAnimCoords(u8 x, u8 y) {
		u32 player = GameHelper::GetPInstance();
		if(player == 0)
			return 0;
		
		x = *(u8 *)(player + 0x201);
		y = *(u8 *)(player + 0x200);
		return 1;
	}
//Get Animation Object	
	/*u32 GameHelper::AnimationObject() {
		u32 player = GameHelper::GetPInstance();
		
		if(player == 0)
			return 0;
		
		Process::Write32((u32)&pfunction01, 0x556AD4);
		return pfunction01(player + 0xA4);
	}*/
//Get Animation Instance
	u32 GameHelper::GetAnimationInstance() {
		u32 player = GameHelper::GetPInstance();
		
		if(player == 0)
			return 0;
		
		Process::Write32((u32)&pfunction01, 0x4DDE0C);
		return pfunction01(player); //0x769DC4 indoors
	}
//Execute Animation	
	u32 GameHelper::ExecuteAnimation(u8 animID, u32 animInstance) {
		u32 player = GameHelper::GetPInstance();
		
		if(player == 0)
			return 0;
		
		if(animInstance == 0)
			return 0;
		
		Process::Write32((u32)&pfunction04, 0x4D8960);
		return pfunction04(player, animID, animInstance, 0);
	}
//Animation Wrapper
	bool GameHelper::AnimationWrapper(u8 animID, u8 emotion, u32 item) {
		//Get player data
		u32 player = GameHelper::GetPInstance();
		//If player is not loaded return
		if(player == 0)
			return 0;
		//Get Animation Data
		u32 animInstance;
		animInstance = GameHelper::GetAnimationInstance();
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
		//outfit change and hold item
		else if(animID == 0x42 || animID == 0x43) {
			Process::Write8(animInstance + 0x1C, item);
			Process::Write8(animInstance + 0x20, emotion);
			Process::Write32(animInstance + 0x44, 0x02880000);
		}
		
		//Execute standard Animation
		GameHelper::ExecuteAnimation(animID, animInstance);
	
		Sleep(Milliseconds(25));
		return 1;
	}
}