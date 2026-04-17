#pragma once

#include <CTRPluginFramework.hpp>
#include "core/game_api/GameStructs.hpp"

namespace CTRPluginFramework {
	namespace Game {
		struct WorldCoord {
			u32 wX;
			u32 wY;
		};

		/*
		0x49C984 setHairStyle(u8 hairStyleId);
		*/

		void 				AppearanceUpdate();
		bool				IsRoomLoading();
		TakumiData*			GetTakumiSaveData();
		ACHHD_Data*			GetSaveData();
		ACHHD_Player*		GetPlayerSaveData();
		u32 				GetAcPlayerInstance();
		u32					GetCurrentMap();
		u8 					GetStageID();
		u32 				*GetItemAtWorldCoords(WorldCoord worldCoords);
		u32					RoomChange(u8 room);
		bool 				Outside();
		float           	*GetCoordinates();
		float 				*WorldCoordsToCoords(WorldCoord worldCoords, float res[3]);
		void 				DropItem(u32 *ItemID, WorldCoord worldCoords);
		WorldCoord			GetWorldCoords();
	}
}