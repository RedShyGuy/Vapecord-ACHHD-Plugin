#include <CTRPluginFramework.hpp>
#include "features/cheats.hpp"
#include "core/infrastructure/Address.hpp"
#include "core/Config.hpp"
#include "core/infrastructure/PluginUtils.hpp"
#include "core/game_api/Game.hpp"
#include "Files.h"

namespace CTRPluginFramework {
	static const std::string NOTE =
        std::string(
R"(Creator: Kwadukathole (Lukas)

Cheat Credits: Kominost (Walk Over Things)

)") + Utils::Format("Discord: %s", DISCORDINV);

	static const std::string GameVersion = "2.0";

	extern int UI_Pos;
	bool OSD_SplashScreen(const Screen &Splash);
	void InitMenu(PluginMenu *menu);

	enum GameVersionResult {
		CORRECT_VERSION,
		STRING_NOT_FOUND,
		WRONG_VERSION
	};

	GameVersionResult IsNewestVersion(std::string& versionSTR, const std::string& gameVersion) {
		versionSTR.clear();

		static const std::vector<u16> Pattern = { 0x0056, 0x0065, 0x0072, 0x002E, 0x0020 };
		u16* found = (u16 *)Utils::Search<u16>(0x00600000, 0x00200000, Pattern);
		if(found == nullptr) {
			return STRING_NOT_FOUND;
		}

		versionSTR = Utils::Format("%c.%c", (char)found[5], (char)found[7]);
		if(versionSTR != gameVersion) {
			return WRONG_VERSION;
		}

		return CORRECT_VERSION;
	}

	bool CheckGameVersion(void) {
		std::string currentVersion = "";
		GameVersionResult res = IsNewestVersion(currentVersion, GameVersion);

		if(res == WRONG_VERSION) {
			Sleep(Seconds(5));
			static const std::string str = Utils::Format("Your game has the version %s\nThis plugin only supports the game version %s.\nDo you still want to try it out?", currentVersion.c_str(), GameVersion.c_str());
            if((MessageBox(Color(0xDC143CFF) << "Warning, wrong game version!", str, DialogType::DialogYesNo)).SetClear(ClearScreen::Top)()) {
				return true;
			}

			return false;
		}

		else if(res == STRING_NOT_FOUND) {
			OSD::NotifySysFont("Game Version Not Found!");
			return false;
		}

		return true;
	}

	/*
	479038 room loading gets unset while game launches
	First called by 16E86C
	Second called by 522af0

	479180 room loading gets set again afterwards
	*/

	bool gameLoading = true;

	void SleepTime(void) {
		static Hook sleepHook;
		static Address loadFunc(0x522AF0);
		
		const auto loadStartUpScreen = +[](u32 u0) -> u32 {
			gameLoading = false;

			HookContext& ctx = HookContext::GetCurrent();
			return ctx.OriginalFunction<u32, u32>(u0);
		};

		sleepHook.InitializeForMitm(loadFunc.addr, (u32)loadStartUpScreen);
		sleepHook.Enable();

		OSD::Run(OSD_SplashScreen);

		constexpr int tick_ms  = 150;
		constexpr int ui_cycle = 8;

		while(gameLoading) { //title screen
			UI_Pos = (UI_Pos + 1) % ui_cycle;
			Sleep(Milliseconds(tick_ms));
		}

		OSD::Stop(OSD_SplashScreen);

		sleepHook.Disable();
	}

	void PerformAutoSaveBackup(void);
	void ShowAntiScamScreen(void);

	void ToolFix(void);
	void UmbrellaSecretEquip(void);

	int	main(void) {
		std::string region = Address::LoadRegion();

		PluginMenu *menu = new PluginMenu(Color::White << "ACHHD Vapecord Plugin " << region, majorV, minorV, revisV, NOTE);
		menu->SynchronizeWithFrame(true);
		menu->ShowWelcomeMessage(false);

	//If title isn't ACHHD
		if(region.empty()) {
			OSD::NotifySysFont("Plugin ready!");
			menu->Run();
			return 0;
		}

		if (!CheckGameVersion()) {
			OSD::NotifySysFont("Plugin ready!");
			menu->Run();
			return 0;
		}

	//This gets set here and not in the PatchProcess because it should only be set if the game is new leaf
		FwkSettings &settings = FwkSettings::Get();
		settings.SaveBackupCallback = PerformAutoSaveBackup;
		settings.SaveBackupMaxSlots = 3; //3 is currently the default

		if (!Config::EnsureConfigFile()) {
			OSD::NotifySysFont("Failed to create config file!", Color::Red);
			menu->Run();
			return 0;
		}

		Config::HandleConfigMigration();

		SleepTime();

		Config::SetupLanguage(false);

	//Show anti-scam warning on first launch
		ShowAntiScamScreen();

	//Load MenuFolders and Entrys (located in MenuCreate.cpp)
		InitMenu(menu);

	//Load Callbacks
		menu->Callback(ToolFix);
		menu->Callback(UmbrellaSecretEquip);
		Process::exceptionCallback = CustomExceptionHandler;

		OSD::NotifySysFont("ACHHD Vapecord Plugin ready!");
	//Run Menu Loop
		menu->Run();
		return 0;
	}
}
