#ifndef GAMEHELPER_HPP
#define GAMEHELPER_HPP

#include "CTRPluginFramework.hpp"
#include "Helpers/Wrapper.hpp"

namespace CTRPluginFramework {
	namespace GameHelper {
		std::string 	GetStageName(u8 stageID = 0);
		u32				GetTakumi();
		u32				GetPlayerData();
		u32				GetPlayerOffset();
		u32 			GetPInstance();
		u32				GetCurrentMap();
		u8 				GetStageID();
		u32 			*GetItemAtWorldCoords(Coord worldCoords);
		u32				RoomChange(u8 room);
		bool 			Outside();
		float           *GetCoordinates();
		float 			*WorldCoordsToCoords(Coord worldCoords, float res[3]);
		void 			DropItem(u32 *ItemID, Coord worldCoords);
		Coord			GetWorldCoords();
	}
}
#endif