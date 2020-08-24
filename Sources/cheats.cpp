#include "cheats.hpp"

namespace CTRPluginFramework
{
	vu32(*pfunction00)();
	vu32(*pfunction01)(u32 param1);
	vu32(*pfunction02)(u32 param1, u32 param2);
	vu32(*pfunction03)(u32 param1, u32 param2, u32 param3);
	vu32(*pfunction04)(u32 param1, u32 param2, u32 param3, u32 param4);
	vu32(*pfunction05)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
	vu32(*pfunction06)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
	vu32(*pfunction07)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
	vu32(*pfunction08)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
	vu32(*pfunction09)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9);
	vu32(*pfunction010)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10);
	vu32(*pfunction011)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10, u32 param11);

	bool SetUpKB(const std::string &msg, bool hex, const int length, u64 &output, u64 def, OnInputChange cb) {
		Sleep(Milliseconds(100));
		Keyboard kb("");
		kb.GetMessage() = msg;
		kb.IsHexadecimal(hex);
		kb.SetMaxLength(length);
		kb.OnInputChange(cb);
		return kb.Open(output, def) == 0;
	}

	bool SetUpKB(const std::string &msg, bool hex, const int length, u32 &output, u32 def, OnInputChange cb) {
		Sleep(Milliseconds(100));
		Keyboard kb("");
		kb.GetMessage() = msg;
		kb.IsHexadecimal(hex);
		kb.SetMaxLength(length);
		kb.OnInputChange(cb);
		return kb.Open(output, def) == 0;
	}

	bool SetUpKB(const std::string &msg, bool hex, const int length, u16 &output, u16 def, OnInputChange cb) {
		Sleep(Milliseconds(100));
		Keyboard kb("");
		kb.GetMessage() = msg;
		kb.IsHexadecimal(hex);
		kb.SetMaxLength(length);
		kb.OnInputChange(cb);
		return kb.Open(output, def) == 0;
	}

	bool SetUpKB(const std::string &msg, bool hex, const int length, u8 &output, u8 def, OnInputChange cb) {
		Sleep(Milliseconds(100));
		Keyboard kb("");
		kb.GetMessage() = msg;
		kb.IsHexadecimal(hex);
		kb.SetMaxLength(length);
		kb.OnInputChange(cb);
		return kb.Open(output, def) == 0;
	}
}