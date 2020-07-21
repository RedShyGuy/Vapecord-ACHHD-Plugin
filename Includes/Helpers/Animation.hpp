#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
	class Animation
	{
	public:
		static u8 		GetCurrentAnim();
		static u16		GetCurrentSnake();
		static u32		GetAnimationInstance();
		static u32		ExecuteAnimation(u8 animID, u32 animInstance);
		static bool 	AnimationWrapper(u8 animID, u8 emotion, u16 item, u16 snake, u16 sound);
	};
}
#endif