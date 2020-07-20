#ifndef CHEATS_H
#define CHEATS_H

#include "CTRPluginFramework.hpp"
#include <cmath>
#include <algorithm>
	
namespace CTRPluginFramework
{		
	using OnInputChange = void(*)(Keyboard &keyboard, InputChangeEvent &event);
	void collisions(MenuEntry *entry);
	void saverestore(MenuEntry *entry);
	void savedump(MenuEntry *entry);
	void playerchange(MenuEntry *entry);
	void debug(MenuEntry *entry);
	void fastgamespeed(MenuEntry *entry);
	void idle(MenuEntry *entry);
	void setanim(MenuEntry *entry);
	void miscFunctions(MenuEntry *entry);
	void roomwarp(MenuEntry *entry);
	void coordmod(MenuEntry *entry);
	void coordspeed(MenuEntry *entry);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u64 &output, u64 def, OnInputChange cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u32 &output, u32 def, OnInputChange cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u16 &output, u16 def, OnInputChange cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u8 &output, u8 def, OnInputChange cb = nullptr);
}

#endif