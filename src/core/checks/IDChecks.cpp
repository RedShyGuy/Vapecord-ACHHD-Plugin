#include "core/checks/IDChecks.hpp"
#include "core/infrastructure/Address.hpp"
#include "core/infrastructure/Language.hpp"
#include "core/Converters.hpp"
#include "core/RuntimeContext.hpp"
#include "core/game_api/GameStructs.hpp"

namespace CTRPluginFramework {
	namespace {
		inline bool In16BitRange(u32 value, u16 start, u16 end) {
			const u16 value16 = static_cast<u16>(value & 0xFFFF);
			return value16 >= start && value16 <= end;
		}

		inline bool Is16BitEqual(u32 value, u16 compare) {
			return static_cast<u16>(value & 0xFFFF) == compare;
		}
	}

	Range KeyRange::sRange;

	void ValidKeyboardCheck(Keyboard& keyboard, KeyboardEvent& event) {
		std::string& input = keyboard.GetInput();	
		u16 ID = Convert::StringToHex<u16>(input, 0xFFFF);
		if(!IDChecks::IsInRange((ID & 0xFFFF), KeyRange::sRange.start, KeyRange::sRange.end)) {
			keyboard.SetError(Color::Red << Language::getInstance()->get(TextID::INVALID_ID));
			return;
		}
	}

	void ItemChange(Keyboard& keyboard, KeyboardEvent& event) {
		std::string& input = keyboard.GetInput();	
		Item ID = (Item)Convert::StringToHex<u32>(input, 0xFFFF);
		if(!ID.isValid()) {
			keyboard.SetError(Color::Red << Language::getInstance()->get(TextID::INVALID_ID));
			return;
		}
	}

	void TextItemChange(Keyboard& keyboard, KeyboardEvent& event) {
		std::string& input = keyboard.GetInput();
		Item ID = (Item)Convert::StringToHex<u32>(input, 0xFFFF);

		if(!ID.isValid(false)) {
			keyboard.GetMessage() = "";
			keyboard.SetError(Color::Red << Language::getInstance()->get(TextID::INVALID_ID));
			return;
		}

		keyboard.GetMessage() = ID.GetName();
	}

	bool IDChecks::StageValid(u8 stageID) {
		return true;
	}

	bool IDChecks::EmotionValid(u8 emotionID) {
		return true;
	}

	bool IDChecks::SnakeValid(u16 snakeID) {
		return true;
	}

	bool IDChecks::AnimationValid(u8 animID, u8 playerIndex) {
		return true;
	}

	std::string IDChecks::GetStageName(u8 ID) {
		static Address stageFunc(0x496FA8);
		return (std::string)stageFunc.Call<char *>(ID);
	}
	
	bool IDChecks::IsInRange(u16 ID, u16 startID, u16 endID) {
		return (ID >= startID && ID <= endID);
	}
}