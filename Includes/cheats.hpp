#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers/GameHelper.hpp"
#include "Helpers/Animation.hpp"
#include "CTRPluginFramework/System/Rect.hpp"
#include "MenuEntryhelpers.hpp"
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
	using OnChangeCallback  = void(*)(Keyboard &keyboard, KeyboardEvent &event);
	
	extern vu32(*FUN)(...);
	
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
	void Dropper(MenuEntry *entry);
	void FunctionsCaller(MenuEntry *entry);
	void fastgamespeed(MenuEntry *entry);
	
	//Unused For Now
	void playerchange(MenuEntry *entry);
	
	//Helper Keyboards
	bool SetUpKB(const std::string &msg, bool hex, const int length, u64 &output, u64 def, OnChangeCallback cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u32 &output, u32 def, OnChangeCallback cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u16 &output, u16 def, OnChangeCallback cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u8 &output, u8 def, OnChangeCallback cb = nullptr);
}

#endif