#pragma once

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
	namespace Game {
		struct WorldCoord {
			u32 wX;
			u32 wY;
		};

		bool				IsRoomLoading();
		u32					GetTakumi();
		u32					GetPlayerData();
		u32					GetPlayerOffset();
		u32 				GetPInstance();
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