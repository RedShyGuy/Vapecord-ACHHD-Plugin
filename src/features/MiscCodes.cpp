#include "features/cheats.hpp"
#include "core/game_api/Game.hpp"
#include "core/game_api/Animation.hpp"
#include "core/infrastructure/PluginUtils.hpp"
#include "core/infrastructure/Address.hpp"

namespace CTRPluginFramework {
	bool debugOSD(const Screen &screen) {
		if(Game::GetAcPlayerInstance() == 0) 
			return 0;
		
		volatile float *pCoords = Game::GetCoordinates();

		Game::WorldCoord worldCoords = Game::GetWorldCoords();
		u32 ItemOffset = (u32)Game::GetItemAtWorldCoords(worldCoords);
		
		if(screen.IsTop) {
			screen.Draw("Coordinates: " << std::to_string(*pCoords).erase(4) << "|" << std::to_string(*((float *)((vu32)pCoords + 8))).erase(4), 0, 0);
			screen.Draw(Utils::Format("World Coordinates: %02X|%02X", worldCoords.wX, worldCoords.wY), 0, 10);
			screen.Draw(Utils::Format("Room: %02X", Game::GetStageID()), 0, 20);
			screen.Draw(Utils::Format("Animation: %02X", Animation::GetCurrentAnim()), 0, 30);
			screen.Draw(Utils::Format("Snake: %03X", Animation::GetCurrentSnake()), 0, 40);
			screen.Draw("Standing on: " << (ItemOffset != 0 ? Utils::Format("%08X", *(u32 *)ItemOffset) : "N/A"), 0, 50);
		}
		return 1;
	} 
	
	void debug(MenuEntry *entry) {
		if(entry->WasJustActivated()) 
			OSD::Run(debugOSD);
		else if(!entry->IsActivated()) 
			OSD::Stop(debugOSD);
	}
	
	void Dropper(MenuEntry *entry) {
		if(Game::GetAcPlayerInstance() == 0) 
			return;
		
		static u32 ItemID = 0x7FFE;
		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			PluginUtils::Input::PromptNumber<u32>({ "Enter Item ID:", true, 8, ItemID, nullptr }, ItemID);
		}
		
		if(entry->Hotkeys[1].IsDown()) {
			if(Game::GetStageID() == 1) {
				Game::WorldCoord worldCoords = Game::GetWorldCoords();
				Game::DropItem(&ItemID, worldCoords);
			}
		}
	}

	void unlockshops(MenuEntry *entry) {
		//u32 p = Game::GetPlayerOffset();
		//Main Street
		//School = 	 p + 0x1B4D80
		//Hospital = p + 0x1B5EB8
		//Cafe = 	 p + 0x1B6FF0
		//Store = 	 p + 0x1B8128
		
		//Idk = 	 p + 0x1B9260
		//Idk =		 p + 0x1BA398
		
	}

	void fastgamespeed(MenuEntry *entry) { 	
		static Address fastGame(0x44DAF4);
		if (entry->WasJustActivated()) 
			fastGame.Patch(0xE3E004FF);
		else if (!entry->IsActivated()) 	
			fastGame.Unpatch();
	}
}