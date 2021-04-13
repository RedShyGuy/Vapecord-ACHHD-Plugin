#include "cheats.hpp"
#include <cstdarg>

namespace CTRPluginFramework {
//Dump File	
	ExHandler Wrap::Dump(const std::string& path, std::string& filename, const std::string& filetype, WrapLoc dump, ...) {
		File file; 
		Directory dir(path, true);     
			
		if(filename.find(filetype) == std::string::npos) 
			filename += filetype;    
			
	//Couldnt open file			
		if(dir.OpenFile(file, filename, File::RWC) != 0) {
			MessageBox("Error\nCouldn't create/open file.").SetClear(ClearScreen::Top)();
			return ExHandler::ERROR_OP; //error opening file
		}

		va_list dumps;
		va_start(dumps, dump);

		while(dump.Address != 0xFFFFFFFF) { //the last arg needs to be -1 in order for the while loop to exit
			if(file.Dump(dump.Address, dump.Lenght) != 0) {
				MessageBox("Error\nCouldn't dump file.").SetClear(ClearScreen::Top)();
				return ExHandler::ERROR_DRD; //error dumping file
			}

			dump = va_arg(dumps, WrapLoc); //go to next argument		
		}
		va_end(dumps);

		MessageBox("File dumped to:\n" + file.GetFullName()).SetClear(ClearScreen::Top)();
		return ExHandler::SUCCESS; //success
	}
//Restore file
	ExHandler Wrap::Restore(const std::string& path, const std::string& filetype, const std::string& KBMsg, OnChangeCallback cb, WrapLoc rest, ...) { 
		std::vector<std::string> f_list;
		File file;
		Directory dir(path);

		if(dir.ListFiles(f_list, filetype) == Directory::OPResult::NOT_OPEN)
			return ExHandler::ERROR_UN;

		if(f_list.empty()) {
            MessageBox("Error\nCouldn't find any files to restore.").SetClear(ClearScreen::Top)();
            return ExHandler::ERROR_LI; //error listing files
        }

		Keyboard kb(KBMsg);
		kb.Populate(f_list);
		kb.OnKeyboardEvent(cb);

		int uchoice = kb.Open();	
		if(uchoice == -1) 
			return ExHandler::ERROR_UN;
			
		if(dir.OpenFile(file, f_list[uchoice], File::RWC) != 0) {
			MessageBox("Error\nCouldn't open file.").SetClear(ClearScreen::Top)();
			return ExHandler::ERROR_OP; //error opening file
		}

		va_list restore;
		va_start(restore, rest);

		while(rest.Address != 0xFFFFFFFF) {
			if(file.Inject(rest.Address, rest.Lenght) != 0) {
				MessageBox("Error\nCouldn't inject file.").SetClear(ClearScreen::Top)();
				return ExHandler::ERROR_DRD; //error injecting file
			}

			rest = va_arg(restore, WrapLoc); //go to next argument
		}
		va_end(restore);

		MessageBox("Successfully restored your file!").SetClear(ClearScreen::Top)();
		return ExHandler::SUCCESS; //success
	}

	ExHandler Wrap::Delete(const std::string& path, const std::string& filetype) { 
		std::vector<std::string> f_list;
		File file;
		Directory dir(path);

		if(dir.ListFiles(f_list, filetype) == Directory::OPResult::NOT_OPEN)
			return ExHandler::ERROR_UN; //couldnt open directory

		if(f_list.empty()) {
            MessageBox("Error\nCouldn't find any files to delete.").SetClear(ClearScreen::Top)();
            return ExHandler::ERROR_LI; //error listing files | no files found
        }

		Keyboard kb("");
		kb.Populate(f_list);
		//kb.OnKeyboardEvent(cb);

		int uchoice = kb.Open();	
		if(uchoice == -1) 
			return ExHandler::ERROR_UN;

		if(dir.OpenFile(file, f_list[uchoice], File::RWC) != 0) {
			MessageBox("Error\nCouldn't open file.").SetClear(ClearScreen::Top)();
			return ExHandler::ERROR_OP; //error opening file
		}

		if((MessageBox("Do you really want to delete " << f_list.at(uchoice) << "?", DialogType::DialogYesNo)).SetClear(ClearScreen::Top)()) {
			File::Open(file, (path << std::string("/") << f_list.at(uchoice)), File::Mode::WRITE);
			file.Flush();
			file.Close();
			if(File::Remove(path << std::string("/") << f_list.at(uchoice)) != 0) {
				MessageBox("Error\nCouldn't delete file.").SetClear(ClearScreen::Top)();
				return ExHandler::ERROR_DRD; //error deleting file
			}
			MessageBox(f_list.at(uchoice) << " deleted!").SetClear(ClearScreen::Top)();
		}
		dir.Close();	
		return ExHandler::SUCCESS; //success
	}
}