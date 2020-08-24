#include "cheats.hpp"
#include "Helpers/GameHelper.hpp"

//0x739814 is 7FFE Pointer

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
		if(i == 0) 
			return 0;
		
		i += 0x50;
		
		return(float *)i;
	}
//get world coords
	u32 GameHelper::GetWorldCoords() {
		u32 i = GameHelper::GetPInstance();
		if(i == 0) 
			return 0;
		
		i += 0x59C;	
		
		return i;
	}
//Get current map	
	u32 GameHelper::GetCurrentMap() {
		Process::Write32((u32)&pfunction00, 0x50B1F8);
		return pfunction00();
	}
//get item at world coords
	u32 *GameHelper::GetItemAtWorldCoords(u32 wX, u32 wY) {
		Process::Write32((u32)&pfunction04, 0x57C890);
		return (u32 *)pfunction04(GameHelper::GetCurrentMap(), wX, wY, 0);
	}
//drop function
	void GameHelper::DropItem(u32 ItemID, u32 wX, u32 wY) {
		u32 i = GameHelper::GetPInstance();
		if(i == 0) 
			return;

		Process::Write32(0x7ED000, ItemID);
		Process::Write32((u32)&pfunction04, 0x480BDC);
		pfunction04(0x7ED000, wX, wY, 0);
	}
	
//Converts world coords to coords
	float *GameHelper::WorldCoordsToCoords(u8 wX, u8 wY, float res[3]) {
		volatile float *coords = GameHelper::GetCoordinates();
		if(coords != nullptr) 
			res[1] = *(volatile float *)((u32)coords + 4);
		
		res[0] = (float)(wX * 0x20 + 0x10);
		res[2] = (float)(wY * 0x20 + 0x10);
		return &res[0];
	}
//If outside
	bool GameHelper::Outside() {
		if(*(u32 *)0x33672A00 != 0) 
			return false;

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
}