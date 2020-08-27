#ifndef GAMEHELPER_HPP
#define GAMEHELPER_HPP

#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
	class GameHelper
	{
	public:
		static u32		GetPlayerData();
		static u32		GetPlayerOffset();
		static u32 		GetPInstance();
		static u32		GetCurrentMap();
		static u32 		*GetItemAtWorldCoords(u32 wX, u32 wY);
		static u32		RoomChange(u8 room);
		static bool 	Outside();
		static u32	 	GetCoordinates();
		static float 	*WorldCoordsToCoords(u8 wX, u8 wY, float res[3]);
		static void 	DropItem(u32 ItemID, u32 wX, u32 wY);
		static u32		GetWorldCoords();
	};
	
	class Region
	{
	public:
		static int AutoRegion(u32 usa, u32 eur, u32 jpn);
	};
}
#endif