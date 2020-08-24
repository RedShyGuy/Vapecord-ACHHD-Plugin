#include "cheats.hpp"
#include "Helpers/GameHelper.hpp"

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
		else 
			return 0;
		
		return(float *)i;
	}
//get world coords
	u32 GameHelper::GetWorldCoords() {
		u32 i = GameHelper::GetPInstance();
		if(i != 0) 
			i += 0x59C;
		else 
			return 0;
		
		return i;
	}
//If outside
	bool GameHelper::Outside() {
		if(*(u32 *)0x33672A00 != 0) 
			return false;
		else 
			return true;
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
}//