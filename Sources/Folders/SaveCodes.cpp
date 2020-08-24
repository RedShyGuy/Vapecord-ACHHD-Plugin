#include "cheats.hpp"

namespace CTRPluginFramework
{
//Restore or dump TAKUMI save
	void SaveSettings(MenuEntry *entry) {
		std::vector<std::string> options = 
		{
			"Dump TAKUMI", 
			"Restore TAKUMI",  
		};
		
		Keyboard KB("Choose Option:");
		KB.Populate(options);
		File TAKUMI;
		
		switch(KB.Open()) {
			case -1: break;
			case 0: {
				Directory dir("TAKUMI", true);     
				Keyboard keyboard("Dump your TAKUMI Save");
				std::string savename; 
				if(keyboard.Open(savename) != -1) {
					
					if(savename.find(".dat") == std::string::npos) 
						savename += ".dat";               
					
					if(dir.OpenFile(TAKUMI, savename, File::RWC) == 0) {
						
						if(TAKUMI.Dump(0x324A8340, 0x2BE930) == 0)
							MessageBox("File Dumped: " + TAKUMI.GetFullName())();
						
						else 
							MessageBox("Dump Error", "Could not dump file!")(); 
					}
					else 
						MessageBox("Dump Error", "Could not open file!")();
				}
			} break;
			case 1: {
				std::vector<std::string> files;
				Directory::Create("TAKUMI");
				Directory dir;
				Directory::Open(dir, "TAKUMI", true);
				dir.ListFiles(files, ".dat");
				Keyboard kb("Select TAKUMI save to restore");
				kb.Populate(files);
				int userchoice = kb.Open();
				if(userchoice != -1) {
					if(dir.OpenFile(TAKUMI, files[userchoice], File::RWC) == 0) {
						if(TAKUMI.Inject(0x324A8340, 0x2BE930) == 0) {
							MessageBox("Restore TAKUMI save was successful!")();
						}
						else MessageBox("Restore Error", "Could not inject TAKUMI save!")();
					}
					else MessageBox("Restore Error", "Could not open file!")();
				}  
			} break;
		}
	}
}//