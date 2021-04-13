#include "cheats.hpp"

//0x739814 is 7FFE Pointer

namespace CTRPluginFramework {
//Get room name
	std::string GameHelper::GetStageName(u8 stageID) {
		static const u32 STAGE_FUN = Region::AutoRegion(0x496FA8, 0x496E90, -1);
		static FUNCT func = FUNCT(STAGE_FUN);
		return (std::string)func.Call<char *>(stageID);
	}
//get takumi
	u32 GameHelper::GetTakumi() {
		static const u32 TAKUMI_FUN = Region::AutoRegion(0x4A0554, 0x4A043C, -1);
		static FUNCT func = FUNCT(TAKUMI_FUN);
		return func.Call<u32>();
	}

	u8 GameHelper::GetStageID() {
		static const u32 ROOMID = Region::AutoRegion(0x496B20, 0x496A08, -1);
		static FUNCT func = FUNCT(ROOMID);
		return func.Call<u8>();
	}
//get player offset
	u32 GameHelper::GetPlayerOffset() {
		static const u32 PLAYER_ADDRESS = Region::AutoRegion(0x4A07B8, 0x4A06A0, -1);
		static FUNCT func = FUNCT(PLAYER_ADDRESS);
		return func.Call<u32>();
	}
//get player start
	u32 GameHelper::GetPlayerData() {
		u32 p = GameHelper::GetPlayerOffset();
		p += 0x1BFA88;
		return p;
	}
//Get Coords
	float *GameHelper::GetCoordinates() {
		u32 i = GameHelper::GetPInstance();
		if(i == 0) 
			return 0;
		
		static const u32 P_COORD = Region::AutoRegion(0x49D5C0, 0x49D4A8, -1);
		static FUNCT func = FUNCT(P_COORD);
		return func.Call<float *>(1);
	}
//get world coords
	Coord GameHelper::GetWorldCoords() {
		u32 i = GameHelper::GetPInstance();
		if(i == 0) 
			return (Coord){ 0, 0 };
		
		i += 0x59C;	
		
		return *(Coord *)i;
	}
//Get current map	
	u32 GameHelper::GetCurrentMap() {
		static const u32 MAP = Region::AutoRegion(0x50B1F8, 0x50B1C4, -1);
		static FUNCT func = FUNCT(MAP);
		return func.Call<u32>();
	}
//get item at world coords
	u32 *GameHelper::GetItemAtWorldCoords(Coord worldCoords) {
		static const u32 ITEMWORLD = Region::AutoRegion(0x57C890, 0x57C860, -1);
		static FUNCT func = FUNCT(ITEMWORLD);
		return func.Call<u32 *>(GameHelper::GetCurrentMap(), worldCoords.wX, worldCoords.wY, 0);
	}
//drop function
	void GameHelper::DropItem(u32 *ItemID, Coord worldCoords) {
		u32 i = GameHelper::GetPInstance();
		if(i == 0) 
			return;

		static const u32 DROP_FUN = Region::AutoRegion(0x480BDC, 0x480AC4, -1);
		static FUNCT func = FUNCT(DROP_FUN);
		func.Call<void>(ItemID, worldCoords.wX, worldCoords.wY, 0);
	}
//Converts world coords to coords
	float *GameHelper::WorldCoordsToCoords(Coord worldCoords, float res[3]) {
		volatile float *coords = (float *)GameHelper::GetCoordinates();
		if(coords != nullptr) 
			res[1] = *(volatile float *)((u32)coords + 4);
		
		res[0] = (float)(worldCoords.wX * 0x20 + 0x10);
		res[2] = (float)(worldCoords.wY * 0x20 + 0x10);
		return &res[0];
	}
//If outside
	bool GameHelper::Outside() {
		static const u32 OUTSIDE = Region::AutoRegion(0x497620, 0x497508, -1);
		static FUNCT func = FUNCT(OUTSIDE);
		return func.Call<bool>(2, GameHelper::GetStageID());
	}
//Call Room Change Function
	u32 GameHelper::RoomChange(u8 room) {
		static const u32 ROOM_FUNC = Region::AutoRegion(0x496F5C, 0x496E44, -1);
		static FUNCT func = FUNCT(ROOM_FUNC);
		return func.Call<u32>(room, 1, 1, 0);
	}
//Get Player Instance
	u32 GameHelper::GetPInstance() {
		static const u32 P_INSTANCE = Region::AutoRegion(0x49DA08, 0x49D8F0, -1);
		static FUNCT func = FUNCT(P_INSTANCE);
		return func.Call<u32>(0, 1);
	}
}