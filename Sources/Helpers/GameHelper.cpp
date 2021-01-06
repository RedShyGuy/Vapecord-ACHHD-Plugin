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
//Get room name
	std::string GameHelper::GetStageName(u8 stageID) {
		Process::Write32((u32)&FUN, 0x496FA8);
		return (std::string)((char *)FUN(stageID));
	}
//get takumi
	u32 GameHelper::GetTakumi() {
		Process::Write32((u32)&FUN, 0x4A0554);
		return FUN();
	}
//get player offset
	u32 GameHelper::GetPlayerOffset() {
		Process::Write32((u32)&FUN, 0x4A07B8);
		return FUN();
	}
//get player start
	u32 GameHelper::GetPlayerData() {
		u32 p = GameHelper::GetPlayerOffset();
		p += 0x1BFA88;
		return p;
	}
//Get Coords
	u32 GameHelper::GetCoordinates() {
		u32 i = GameHelper::GetPInstance();
		if(i == 0) 
			return 0;
		
		Process::Write32((u32)&FUN, 0x49D5C0);
		
		return FUN(1);;
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
		Process::Write32((u32)&FUN, 0x50B1F8);
		return FUN();
	}
//get item at world coords
	u32 *GameHelper::GetItemAtWorldCoords(u32 wX, u32 wY) {
		Process::Write32((u32)&FUN, 0x57C890);
		return (u32 *)FUN(GameHelper::GetCurrentMap(), wX, wY, 0);
	}
//drop function
	void GameHelper::DropItem(u32 *ItemID, u32 wX, u32 wY) {
		u32 i = GameHelper::GetPInstance();
		if(i == 0) 
			return;

		Process::Write32((u32)&FUN, 0x480BDC);
		FUN((u32)ItemID, wX, wY, 0);
	}
//Converts world coords to coords
	float *GameHelper::WorldCoordsToCoords(u8 wX, u8 wY, float res[3]) {
		volatile float *coords = (float *)GameHelper::GetCoordinates();
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
		Process::Write32((u32)&FUN, 0x496F5C);
		return FUN(room, 1, 1, 0);
	}
//Get Player Instance	
	u32 GameHelper::GetPInstance() {
		Process::Write32((u32)&FUN, 0x49DA08);
		return FUN(0, 1);
	}
}