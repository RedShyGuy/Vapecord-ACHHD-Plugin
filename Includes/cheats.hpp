#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include <3ds.h>
#include "Helpers/GameHelper.hpp"
#include "Helpers/Animation.hpp"
	
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
	
	class Code
	{
	public:
		
		static void     Load(void);
		static u32		ROOM_ID;
	};

	//Helper Keyboards
	bool SetUpKB(const std::string &msg, bool hex, const int length, u64 &output, u64 def, OnChangeCallback cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u32 &output, u32 def, OnChangeCallback cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u16 &output, u16 def, OnChangeCallback cb = nullptr);
	bool SetUpKB(const std::string &msg, bool hex, const int length, u8 &output, u8 def, OnChangeCallback cb = nullptr);
}

#endif