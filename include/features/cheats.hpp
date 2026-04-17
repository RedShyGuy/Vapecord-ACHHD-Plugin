#pragma once

#include <CTRPluginFramework.hpp>
#include <3ds.h>
	
namespace CTRPluginFramework {
//SaveCodes
	void SaveSettings(MenuEntry *entry);
	void UnlockAllHappyHomeHandbookLessons(MenuEntry *entry);
	void NameEditor(MenuEntry *entry);
	void AppearanceEditor(MenuEntry *entry);
	
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
	void fastgamespeed(MenuEntry *entry);
	void AmiiboSpoofer(MenuEntry *entry);

//DevCodes
	void FunctionsCaller(MenuEntry *entry);
	void PlayerFlagsMonitor(MenuEntry* entry);
	void SetPlayerFlags(MenuEntry *entry);
	void TestEntry(MenuEntry *entry);
	
//Unused For Now
	void playerchange(MenuEntry *entry);

	void pluginSettingsEntry(MenuEntry *entry);
}