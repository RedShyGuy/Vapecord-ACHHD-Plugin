#ifndef GAMEHELPER_HPP
#define GAMEHELPER_HPP

#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
	class GameHelper
	{
	public:
		static u32 		GetPInstance();
		static u32		RoomChange(u8 room);
		static bool 	Outside();
		static float 	*GetCoordinates();
		static u32		GetWorldCoords();
	};
	
	class Region
	{
	public:
		static int AutoRegion(u32 usa, u32 eur, u32 jpn);
	};
}
#endif