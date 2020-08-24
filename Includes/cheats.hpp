#ifndef CHEATS_H
#define CHEATS_H

#include "CTRPluginFramework.hpp"
#include "Helpers/GameHelper.hpp"
#include "Helpers/Animation.hpp"
#include "CTRPluginFramework/System/Rect.hpp"
#include "MenuEntryhelpers.hpp"
#include "ctrulib/util/utf.h"
#include "strings.hpp"
#include <cmath>
#include <algorithm>

#define READU32(x)      *(u32 *)(x)
#define READU16(x)      *(u16 *)(x)
#define READU8(x)       *(u8 *)(x)
#define READFLOAT(x)    *(float *)(x)

#define WRITEU8(a, v)   *(u8 *)(a) = (u8)v
#define WRITEU16(a, v)  *(u16 *)(a) = (u16)v
#define WRITEU32(a, v)  *(u32 *)(a) = (u32)v 
#define WRITEU64(a, v)  *(u64 *)(a) = (u64)v

#define ADD32(a, v)     *(u32 *)a += v
#define SUB32(a, v)     *(u32 *)a -= v
#define ADD64(a, v)     *(vs64 *)a += v
#define SUB64(a, v)     *(vs64 *)a -= v
#define ADD16(a, v)     *(u16 *)a += v
#define SUB16(a, v)     *(u16 *)a -= v
#define ADD8(a, v)      *(u8 *)a += v
#define SUB8(a, v)      *(u8 *)a -= v
#define ADDTOFLOAT(a, v)  *((float*)(a)) += (float)v
#define SUBTOFLOAT(a, v)  *((float*)(a)) -= (float)v
	
namespace CTRPluginFramework
{		
	using OnInputChange = void(*)(Keyboard &keyboard, InputChangeEvent &event);
	
	extern vu32(*pfunction00)();
	extern vu32(*pfunction01)(u32 param1);
	extern vu32(*pfunction02)(u32 param1, u32 param2);
	extern vu32(*pfunction03)(u32 param1, u32 param2, u32 param3);
	extern vu32(*pfunction04)(u32 param1, u32 param2, u32 param3, u32 param4);
	extern vu32(*pfunction05)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
	extern vu32(*pfunction06)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
	extern vu32(*pfunction07)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
	extern vu32(*pfunction08)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
	extern vu32(*pfunction09)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9);
	extern vu32(*pfunction010)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10);
	extern vu32(*pfunction011)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10, u32 param11);
	
	//SaveCodes
	void SaveSettings(MenuEntry *entry);
	
	//MovementCodes
	void collisions(MenuEntry *entry);
	void roomwarp(MenuEntry *entry);
	void coordspeed(MenuEntry *entry);
	void coordmod(MenuEntry *entry);
	
	//AnimationCodes
	void setanim(MenuEntry *entry);
	void idle(MenuEntry *entry);
	void NPCCode(MenuEntry *entry);
	
	//MiscCodes
	void debug(MenuEntry *entry);
	void cameramove(MenuEntry *entry);
	void miscFunctions(MenuEntry *entry);
	void fastgamespeed(MenuEntry *entry);
	
	//Unused For Now
	void playerchange(MenuEntry *entry);
	
	//Helper Keyboards
	bool SetUpKB(const std::string &msg, bool hex, const int length, u64 &output, u64 def, OnInputChange cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u32 &output, u32 def, OnInputChange cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u16 &output, u16 def, OnInputChange cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u8 &output, u8 def, OnInputChange cb = nullptr);
}

#endif