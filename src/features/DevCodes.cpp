#include <CTRPluginFramework.hpp>
#include "core/infrastructure/PluginUtils.hpp"
#include "core/game_api/Game.hpp"
#include "core/game_api/Animation.hpp"
#include "core/game_api/NPC.hpp"
#include "core/infrastructure/Address.hpp"

namespace CTRPluginFramework {
    static bool Turbo_Call = false;

	void FunctionsCaller(MenuEntry *entry) {
		static u32 funcaddress;
		static u32 p[11];
		u32 result;
		static int size;

        if (Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			if (PluginUtils::Input::PromptNumber<u32>({ "Enter address of function:", true, 8, funcaddress, nullptr }, funcaddress)) {
				Keyboard KB("Enter ID:");
				KB.SetMaxLength(8);
				KB.IsHexadecimal(true);
				for (int i = 0; i < 12; i++) {
					Sleep(Milliseconds(100));
					KB.GetMessage() = "Enter value for param " << std::to_string(i) << ":" << 
					"\n" << Color::Blue << "0x11111111 for player instance" << 
					"\n" << Color::Red << "0x22222222 for animation instance" << 
					"\n" << Color::Green << "0x33333333 for map offset";
					
					if (KB.Open(p[i]) == -1) {
						size = i--;
						OSD::NotifySysFont(Utils::Format("Set Function: %08X with %02d parameters!" , funcaddress, size));
						return;
					}

					switch (p[i]) {
						case 0x11111111: 
							p[i] = Game::GetAcPlayerInstance();
						break;

						case 0x22222222:
							p[i] = Animation::GetAnimationInstance();
						break;

						case 0x33333333:
							p[i] = Game::GetCurrentMap();
						break;
					}
				}	
			}
        }

		if (Turbo_Call ? Controller::IsKeysDown(entry->Hotkeys[1].GetKeys()) : Controller::IsKeysPressed(entry->Hotkeys[1].GetKeys())) {
			if (!Process::CheckAddress(funcaddress))
				return;

			Sleep(Milliseconds(100));
			static Address func(funcaddress);
			switch (size) {
				case 0: result = func.Call<u32>(); break;
				case 1: result = func.Call<u32>(p[0]); break;
				case 2: result = func.Call<u32>(p[0], p[1]); break;
				case 3: result = func.Call<u32>(p[0], p[1], p[2]); break;
				case 4: result = func.Call<u32>(p[0], p[1], p[2], p[3]); break;
				case 5: result = func.Call<u32>(p[0], p[1], p[2], p[3], p[4]); break;
				case 6: result = func.Call<u32>(p[0], p[1], p[2], p[3], p[4], p[5]); break;
				case 7: result = func.Call<u32>(p[0], p[1], p[2], p[3], p[4], p[5], p[6]); break;
				case 8: result = func.Call<u32>(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]); break;
				case 9: result = func.Call<u32>(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]); break;
				case 10: result = func.Call<u32>(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]); break;
				case 11: result = func.Call<u32>(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]); break;
			}
			OSD::NotifySysFont(Utils::Format("Returned Value: %08X", result));
		}
    }

    void TestEntry(MenuEntry *entry) {
        if (Controller::IsKeysPressed(Key::A + Key::DPadRight)) {
            TakumiData* tData = Game::GetTakumiSaveData();
			if(tData == nullptr) {
				return;
			}

			ACHHD_Data* data = &tData->data;
			ACHHD_Player* player = &data->player;

            player->flags.unkFlag1 = !player->flags.unkFlag1; //toggle flag 1 for testing

            OSD::NotifySysFont("Flag Toggled! ");
        }
    }

	void SetPlayerFlag(Player_Flags* flags, int index, bool set) {
		if (index < 0 || index >= 176) return;
		u8* flagBytes = reinterpret_cast<u8*>(flags);
		int byte = index / 8;
		int bit = index % 8;
		if (set)
			flagBytes[byte] |= (1 << bit);
		else
			flagBytes[byte] &= ~(1 << bit);
	}

	bool GetPlayerFlag(const Player_Flags* flags, int index) {
		if (index < 0 || index >= 176) return false;
		const u8* flagBytes = reinterpret_cast<const u8*>(flags);
		int byte = index / 8;
		int bit = index % 8;
		return (flagBytes[byte] >> bit) & 1;
	}

	void CheckPlayerFlags(const Player_Flags* flags) {
		static u8 lastFlags[22] = {0}; // 176 bits / 8 = 22 bytes
		static bool initialized = false;

		const u8* flagBytes = reinterpret_cast<const u8*>(flags);
		if (!initialized) {
			memcpy(lastFlags, flagBytes, 22);
			initialized = true;
			return;
		}

		for (int byte = 0; byte < 22; ++byte) {
			u8 diff = lastFlags[byte] ^ flagBytes[byte];
			if (!diff) continue;
			for (int bit = 0; bit < 8; ++bit) {
				if (diff & (1 << bit)) {
					int flagIndex = byte * 8 + bit;
					if (flagIndex >= 176) break;
					OSD::NotifySysFont(Utils::Format("Player Flag %d changed to %d", flagIndex + 1, (flagBytes[byte] >> bit) & 1));
				}
			}
		}
		memcpy(lastFlags, flagBytes, 22);
	}

	void PlayerFlagsMonitor(MenuEntry* entry) {
		TakumiData* tData = Game::GetTakumiSaveData();
		if (tData) {
			CheckPlayerFlags(&tData->data.player.flags);
		}
	}

	void SetPlayerFlags(MenuEntry *entry) {
		Keyboard keyboard("Enter Player Flag Index (1-176):");
		u8 index = 0;
		keyboard.SetMaxLength(3);
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(index) >= 0 && index > 0 && index <= 176) {
			index -= 1; // Convert to 0-based index
			TakumiData* tData = Game::GetTakumiSaveData();
			if (tData) {
				Player_Flags* flags = &tData->data.player.flags;
				bool currentValue = GetPlayerFlag(flags, index);
				SetPlayerFlag(flags, index, !currentValue);
			}
		}
	}
}