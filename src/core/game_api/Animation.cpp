#include "core/game_api/Animation.hpp"
#include "core/game_api/Game.hpp"
#include "core/game_api/AnimData.hpp"
#include "core/infrastructure/Address.hpp"

namespace CTRPluginFramework {
//336729B0, 769DC4
//33673E28, 
//3221 to 3277 tools 
//NPC Animation
	/*void Animation::SetNPCAnimation(u32 npc, u8 animID, u8 emotion, u16 snake) {
		if(animID == 0xC) {
			Process::Write32((u32)&pfunction03, 0x527E5C);
		}
		else if(animID == 0xE) {
			pfunction03(npc, 0, emotion);
			Process::Write32((u32)&pfunction05, 0x528FA0);
			pfunction05(npc, 0, snake, 0, 0);
		}
		else {
			u32 null[]{ 0 };
			Process::Write32((u32)&pfunction08, 0x525A24);
			pfunction08(npc, animID, 0, 0x85A534, (u32)null, (u32)null, 0, 0x66873C);
		}	
	}*/

	u8 Animation::GetCurrentAnim() {
		u32 player = Game::GetAcPlayerInstance();
		if(player == 0)
			return 0;
		
		return(*(u8 *)(player + 0x710));
	}

	u16 Animation::GetCurrentSnake() {
		u32 player = Game::GetAcPlayerInstance();
		if(player == 0)
			return 0;
		
		return(*(u8 *)(player + 0x4CA));
	}

	u32 Animation::GetAnimationInstance() {
		u32 player = Game::GetAcPlayerInstance();
		if(player == 0)
			return 0;

		static Address animInst(0x4DDE0C);
		return animInst.Call<u32>(player);
	}
	
	u32 Animation::ExecuteAnimation(u8 animID, u32 animInstance) {
		u32 player = Game::GetAcPlayerInstance();
		if(player == 0)
			return 0;

		if(animInstance == 0)
			return 0;

		static Address animFunc(0x4D8960);
		return animFunc.Call<u32>(player, animID, animInstance, 0);
	}

	bool Animation::AnimationWrapper(u8 animID, u8 emotion, u16 item, u16 snake, u16 sound) {
		u32 player = Game::GetAcPlayerInstance();
		if(player == 0)
			return 0;

		u32 animInstance = Animation::GetAnimationInstance();
		if(animInstance == 0)
			return 0;

		Game::WorldCoord worldCoords = Game::GetWorldCoords();

		switch(animID) {
			case 0x56:
				AnimData::Emotion_56(animInstance, emotion);
			break;
			case 0x42:
				AnimData::OutfitChange_42(animInstance, emotion, item);
			break;
			case 0x43:
				AnimData::HoldItem_43(animInstance, item);
			break;
			case 0x5A:
				AnimData::Snake_5A(animInstance, player, snake);
			break;
			case 0x18:
			case 0x12:
				AnimData::PickAmiiboPhone_18_12(animInstance);
			break;
			case 0x44:
				AnimData::Null_44(animInstance);
			break;
			case 0x2D:
			case 0x2E:
				AnimData::Sit_2D_2E(animInstance);
			break;
			default:
				AnimData::Null_Default(animInstance, worldCoords);
			break;
		}
		 
		Animation::ExecuteAnimation(animID, animInstance);
	
		Sleep(Milliseconds(25));
		return 1;
	}
}