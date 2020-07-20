#ifndef GAMEHELPER_HPP
#define GAMEHELPER_HPP

#include "CTRPluginFramework.hpp"
#include "strings.hpp"

namespace CTRPluginFramework
{
	class GameHelper
	{
	public:
		static u8 		GetCurrentAnim();
		static u32		GetAInstance();
		static u32 		GetPInstance();
		static u32		RoomChange(u8 room);
		static u32		ExecuteAnimation(u8 animID);
		static float	SetXCoordinates(float speed, bool addsub);
		static float	SetYCoordinates(float speed, bool addsub);
		static float	GetCoordinates();
		static bool 	Outside();
	};
	
	class Region
	{
	public:
		static int AutoRegion(u32 usa, u32 eur, u32 jpn);
	};
}
#endif