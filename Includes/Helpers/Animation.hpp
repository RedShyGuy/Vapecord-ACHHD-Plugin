#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework {
	namespace Animation {
		void	SetNPCAnimation(u32 npc, u8 animID, u8 emotion, u16 snake);
		u8 		GetCurrentAnim();
		u16		GetCurrentSnake();
		u32		GetAnimationInstance();
		u32		ExecuteAnimation(u8 animID, u32 animInstance);
		bool 	AnimationWrapper(u8 animID, u8 emotion, u16 item, u16 snake, u16 sound);
	}
}
#endif