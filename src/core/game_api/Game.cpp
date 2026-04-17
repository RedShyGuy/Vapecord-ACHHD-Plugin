#include "core/game_api/Game.hpp"
#include "core/infrastructure/Address.hpp"

//0x739814 is 7FFE Pointer

namespace CTRPluginFramework {
	void Game::AppearanceUpdate() {
		u32 i = Game::GetAcPlayerInstance();
		if(i == 0) {
			return;
		}
		
		static Address appearanceUpdate(0x4F02FC);
		appearanceUpdate.Call<void>(i, 0);
	}

	bool Game::IsRoomLoading() {
		static const Address LoadCheck(0x73358A);
		return *(bool *)LoadCheck.addr;
	}

	TakumiData* Game::GetTakumiSaveData() {
		static Address takumiFunc(0x4A0554);
		return takumiFunc.Call<TakumiData*>();
	}

	ACHHD_Data*	Game::GetSaveData() {
		TakumiData* tData = GetTakumiSaveData();
		if(!tData) {
			return nullptr;
		}
		return &tData->data;
	}

	ACHHD_Player* Game::GetPlayerSaveData() {
		ACHHD_Data* data = GetSaveData();
		if(!data) {
			return nullptr;
		}
		return &data->player;
	}

	u8 Game::GetStageID() {
		static Address roomId(0x496B20);
		return roomId.Call<u8>();
	}

	float *Game::GetCoordinates() {
		u32 i = Game::GetAcPlayerInstance();
		if(i == 0) 
			return 0;
		
		static Address pCoord(0x49D5C0);
		return pCoord.Call<float *>(1);
	}


	Game::WorldCoord Game::GetWorldCoords() {
		u32 i = Game::GetAcPlayerInstance();
		if(i == 0) 
			return (WorldCoord){ 0, 0 };
		
		i += 0x59C;	
		
		return *(WorldCoord *)i;
	}

	u32 Game::GetCurrentMap() {
		static Address currMap(0x50B1F8);
		return currMap.Call<u32>();
	}

	u32 *Game::GetItemAtWorldCoords(Game::WorldCoord worldCoords) {
		static Address itemAtCoords(0x57C890);
		return itemAtCoords.Call<u32 *>(Game::GetCurrentMap(), worldCoords.wX, worldCoords.wY, 0);
	}

	void Game::DropItem(u32 *ItemID, Game::WorldCoord worldCoords) {
		u32 i = Game::GetAcPlayerInstance();
		if(i == 0) 
			return;

		static Address dropFunc(0x480BDC);
		dropFunc.Call<void>(ItemID, worldCoords.wX, worldCoords.wY, 0);
	}

	float *Game::WorldCoordsToCoords(Game::WorldCoord worldCoords, float res[3]) {
		volatile float *coords = (float *)Game::GetCoordinates();
		if(coords != nullptr) 
			res[1] = *(volatile float *)((u32)coords + 4);
		
		res[0] = (float)(worldCoords.wX * 0x20 + 0x10);
		res[2] = (float)(worldCoords.wY * 0x20 + 0x10);
		return &res[0];
	}

	bool Game::Outside() {
		static Address isOutside(0x497620);
		return isOutside.Call<bool>(2, Game::GetStageID());
	}

	u32 Game::RoomChange(u8 room) {
		static Address roomFunc(0x496F5C);
		return roomFunc.Call<u32>(room, 1, 1, 0);
	}

	u32 Game::GetAcPlayerInstance() {
		static Address pInstance(0x49DA08);
		return pInstance.Call<u32>(0, 1);
	}
}