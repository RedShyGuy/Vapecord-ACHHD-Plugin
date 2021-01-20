#include "cheats.hpp"

namespace CTRPluginFramework
{
	vu32(*FUN)(...);
	
	void Code::Load(void) {
		ROOM_ID = Region::AutoRegion(0x738CE9, -1, -1);
	}

	u32 	Code::ROOM_ID = 0;

	bool SetUpKB(const std::string &msg, bool hex, const int length, u64 &output, u64 def, OnChangeCallback cb) {
		Sleep(Milliseconds(100));
		Keyboard kb("");
		kb.GetMessage() = msg;
		kb.IsHexadecimal(hex);
		kb.SetMaxLength(length);
		kb.OnKeyboardEvent(cb);
		return kb.Open(output, def) == 0;
	}

	bool SetUpKB(const std::string &msg, bool hex, const int length, u32 &output, u32 def, OnChangeCallback cb) {
		Sleep(Milliseconds(100));
		Keyboard kb("");
		kb.GetMessage() = msg;
		kb.IsHexadecimal(hex);
		kb.SetMaxLength(length);
		kb.OnKeyboardEvent(cb);
		return kb.Open(output, def) == 0;
	}

	bool SetUpKB(const std::string &msg, bool hex, const int length, u16 &output, u16 def, OnChangeCallback cb) {
		Sleep(Milliseconds(100));
		Keyboard kb("");
		kb.GetMessage() = msg;
		kb.IsHexadecimal(hex);
		kb.SetMaxLength(length);
		kb.OnKeyboardEvent(cb);
		return kb.Open(output, def) == 0;
	}

	bool SetUpKB(const std::string &msg, bool hex, const int length, u8 &output, u8 def, OnChangeCallback cb) {
		Sleep(Milliseconds(100));
		Keyboard kb("");
		kb.GetMessage() = msg;
		kb.IsHexadecimal(hex);
		kb.SetMaxLength(length);
		kb.OnKeyboardEvent(cb);
		return kb.Open(output, def) == 0;
	}
}