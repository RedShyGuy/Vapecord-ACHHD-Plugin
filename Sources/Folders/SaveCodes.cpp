#include "cheats.hpp"

#define SAVESIZE 0x2BE930

namespace CTRPluginFramework {
//Restore or dump TAKUMI save
	void SaveSettings(MenuEntry *entry) {
		const std::vector<std::string> options = {
			"Dump Save", 
			"Restore Save", 
			"Delete Files", 
		};
		
		Keyboard KB("Choose Option:");
		KB.Populate(options);
		
		switch(KB.Open()) {
			default: break;
			case 0: {
				std::string filename = "";
				Keyboard KB("Dump your Save:");
				if(KB.Open(filename) == -1)
					return;

				Wrap::Dump(PATH_SAVE, filename, ".dat", WrapLoc{ GameHelper::GetTakumi(), SAVESIZE }, WrapLoc{ (u32)-1, (u32)-1 });
			} break;

			case 1: {
				Wrap::Restore(PATH_SAVE, ".dat", "Select your save to restore", nullptr, WrapLoc{ GameHelper::GetTakumi(), SAVESIZE }, WrapLoc{ (u32)-1, (u32)-1 });
			} break;

			case 2: {
				Wrap::Delete(PATH_SAVE, ".dat");
			} break;
		}
	}
}