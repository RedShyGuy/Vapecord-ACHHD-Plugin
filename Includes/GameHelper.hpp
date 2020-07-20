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
		static u32		ExecuteAnimation(u8 animID, u32 animInstance);
		static float	SetXCoordinates(float speed, bool addsub);
		static float	SetYCoordinates(float speed, bool addsub);
		static bool 	Outside();
		static bool 	AnimationWrapper(u8 animID, u8 emotion, u32 item);
		static u32		GetAnimationInstance();
		static u32 		AnimationObject();
		static bool		GetAnimCoords(u8 x, u8 y);
		static float 	*WorldCoordsToCoords(u8 wX, u8 wY, float res[3]);
		static float 	*GetCoordinates();
	};
	
	class Region
	{
	public:
		static int AutoRegion(u32 usa, u32 eur, u32 jpn);
	};
}
#endif