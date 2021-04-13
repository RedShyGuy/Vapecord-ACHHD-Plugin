#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include <3ds.h>
#include "Helpers/GameHelper.hpp"
#include "Helpers/Animation.hpp"
#include "Helpers/Wrapper.hpp"
#include "Helpers/AnimData.hpp"
#include "Helpers/Region.hpp" 

#define PATH_SAVE "Save"
#define DISCORD_LINK "https://discord.gg/QwqdBpKWf3"

#define TITLEID_USA 0x000400000014F100
#define TITLEID_EUR 0x000400000014F200
#define TITLEID_JPN 0x000400000014F000
	
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
}

#endif