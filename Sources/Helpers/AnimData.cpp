#include "cheats.hpp"

namespace CTRPluginFramework {
	template <typename Data>
    void AppendAnimData(u32 animInst, u32 pos, Data data) {
        *(Data *)(animInst + pos) = data;
    }

    void AppendCoordData(u32 animInst, u32 pos, float *Coord) {
		*(float *)(animInst + pos) = Coord[0];
		*(float *)(animInst + pos + 4) = Coord[1];
		*(float *)(animInst + pos + 8) = Coord[2];
    }

	void AnimData::Emotion_56(u32 animInst, u8 emotion) {
		AppendAnimData<u8>(animInst, 0x1C, emotion);
        AppendAnimData<u8>(animInst, 0x1D, 1);
    }

	void AnimData::OutfitChange_42(u32 animInst, u8 emotion, u16 item) {
		AppendAnimData<u32>(animInst, 0x1C, item);
        AppendAnimData<u8>(animInst, 0x20, emotion);
		AppendAnimData<u32>(animInst, 0x44, 0x2880000);
    }

	void AnimData::HoldItem_43(u32 animInst, u16 item) {
		AppendAnimData<u16>(animInst, 0x1C, item & 0xFFFF);
        AppendAnimData<u16>(animInst, 0x1E, (item >> 0x10) & 0xFFFF);
		AppendAnimData<u8>(animInst, 0x20, 1);
    }

	void AnimData::Snake_5A(u32 animInst, u32 playerInst, u16 snake) {
		AppendAnimData<u16>(animInst, 0x1C, snake & 0xFFF);
		AppendAnimData<u16>(animInst, 0x1E, snake & 0xFFFF);

		AppendAnimData<u8>(animInst, 0x20, *(u8 *)(playerInst + 0x6B));
		AppendAnimData<u8>(animInst, 0x21, 1);
		AppendAnimData<u8>(animInst, 0x22, 5);
	}

	void AnimData::PickAmiiboPhone_18_12(u32 animInst) {
		AppendCoordData(animInst, 0x1C, GameHelper::GetCoordinates());
		AppendAnimData<u16>(animInst, 0x28, 0x8258);
    }

	void AnimData::Null_44(u32 animInst) {
		AppendAnimData<u8>(animInst, 0x20, 1);
		AppendAnimData<u8>(animInst, 0x21, 1);
	}

	void AnimData::Sit_2D_2E(u32 animInst) {
		AppendCoordData(animInst, 0x20, GameHelper::GetCoordinates());
		AppendAnimData<u8>(animInst, 0x1C, 2);
	}

	void AnimData::Null_Default(u32 animInst, Coord worldCoords) {
		AppendAnimData<u8>(animInst, 0x1C, worldCoords.wX);
		AppendAnimData<u8>(animInst, 0x1D, worldCoords.wY);
	}
}