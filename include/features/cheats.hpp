#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include <3ds.h>
	
namespace CTRPluginFramework {
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

	void pluginSettingsEntry(MenuEntry *entry);
}

#endif