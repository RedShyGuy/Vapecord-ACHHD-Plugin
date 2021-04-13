#ifndef ANIMDATA_HPP
#define ANIMDATA_HPP

#include "CTRPluginFramework.hpp"
#include "Helpers/Wrapper.hpp"

namespace CTRPluginFramework {
	namespace AnimData {
        void 	Emotion_56(u32 animInst, u8 emotion);
		void 	OutfitChange_42(u32 animInst, u8 emotion, u16 item);
		void 	HoldItem_43(u32 animInst, u16 item);
		void 	Snake_5A(u32 animInst, u32 playerInst, u16 snake);
		void 	PickAmiiboPhone_18_12(u32 animInst);
		void 	Null_44(u32 animInst);
		void 	Sit_2D_2E(u32 animInst);
		void 	Null_Default(u32 animInst, Coord worldCoords);
	}
}
#endif