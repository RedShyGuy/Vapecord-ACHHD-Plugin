#include "features/cheats.hpp"
#include "core/infrastructure/Address.hpp"
#include "core/game_api/Game.hpp"

namespace CTRPluginFramework {
	void playerchange(MenuEntry *entry) {
		static bool speedmode = false;
		
		if(speedmode ? Controller::IsKeysDown(entry->Hotkeys[0].GetKeys()) : Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			//static const u32 pData = Game::GetPlayerData();
			TakumiData* tData = Game::GetTakumiSaveData();
			if(tData == nullptr) {
				return;
			}
			ACHHD_Data* data = &tData->data;
			ACHHD_Player* player = &data->player;

			player->features.HairStyle = Utils::Random(0, 0x1F);
			player->features.Tan = Utils::Random(0, 7);
			player->features.HairColor = Utils::Random(0, 0xF);
			player->features.EyeStyle = Utils::Random(0, 0xC);
			player->features.EyeColor = Utils::Random(0, 5);

			player->outfit.Hat = Utils::Random(0x266A, 0x273E);
			player->outfit.Accessory = Utils::Random(0x273F, 0x2794);
			player->outfit.TopWear = Utils::Random(0x2324, 0x2566);
			player->outfit.BottomWear = Utils::Random(0x2567, 0x25E2);
			player->outfit.Socks = Utils::Random(0x25E3, 0x2606);
			player->outfit.Shoes = Utils::Random(0x2607, 0x2644);
			//player->outfit.HeldItem = Utils::Random(0x3221, 0x3277);
			
			Game::AppearanceUpdate();
			Sleep(Milliseconds(150));
		}

		if(Controller::IsKeysPressed(entry->Hotkeys[1].GetKeys())) {
			speedmode = !speedmode;
			OSD::Notify("Speed Mode " << (speedmode ? (Color::Green << "ON") : (Color::Red << "OFF")));
		}
	}
}