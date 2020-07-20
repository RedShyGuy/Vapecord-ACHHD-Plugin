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

	void playerchange(MenuEntry *entry) {
		/*0x33672DC8 = Hat
		0x33672DCC = Accessoire
		0x33672DD0 = Shirt
		0x33672DD4 = Trousers
		0x33672DD8 = Socks
		0x33672DDC = Shoes*/
	}

	/*void emotionmenu(MenuEntry *entry) { 
		Process::Write32(0x326A8CBC, 0x01020304);
		Process::Write32(0x326A8CC0, 0x05060708);
		Process::Write32(0x326A8CC4, 0x090A0B0C);
		Process::Write32(0x326A8CC8, 0x0D0E1011);
		Process::Write32(0x326A8CCC, 0x12131415);
		Process::Write32(0x326A8CD0, 0x16171819);
		Process::Write32(0x326A8CD4, 0x1A1B1C1D);
		Process::Write32(0x326A8CD8, 0x1E202124);
		Process::Write32(0x326A8CDC, 0x26272829);
		Process::Write32(0x326A8CE0, 0x2A2B2C2E);
		Process::Write32(0x326A8CE4, 0x2F303132);
		Process::Write32(0x326A8CE8, );
	}*/

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