#include "core/Config.hpp"
#include "Color.h"
#include "Files.h"
#include "core/infrastructure/Language.hpp"

namespace CTRPluginFramework {
	static const char* SystemLanguageToShortName(LanguageId id) {
		switch (id) {
			case LanguageId::Japanese:            return "ja";
			case LanguageId::English:             return "en";
			case LanguageId::French:              return "fr";
			case LanguageId::German:              return "de";
			case LanguageId::Italian:             return "it";
			case LanguageId::Spanish:             return "es";
			case LanguageId::ChineseSimplified:   return "zh-CN";
			case LanguageId::Korean:              return "ko";
			case LanguageId::ChineseTraditional:  return "zh-TC";
			case LanguageId::Dutch:               return "nl";
			case LanguageId::Portugese:           return "pt";
			case LanguageId::Russian:             return "ru";
			default:                              return nullptr;
		}
	}

    void Config::SetupLanguage(bool SetInMenu) {
		std::string language = "";
		GetLanguage(language);

		if (!File::Exists(PATH_LANGUAGE_BIN)) {
			MessageBox(Utils::Format("Error 577\nThe language.bin is missing. The Plugin can not work without it!\nGet more info and help on the Discord Server: %s\nGame will be closed now!", DISCORDINV)).SetClear(ClearScreen::Top)();
			Process::ReturnToHomeMenu();
			return;
		}

		if (!Language::getInstance()->verifyVersion(PATH_LANGUAGE_BIN, APP_VERSION)) {
			MessageBox(Utils::Format("Error 606\nThe language.bin version is outdated. Please redownload the latest version of the plugin to get the updated language.bin!\nGet more info and help on the Discord Server: %s\nGame will be closed now!", DISCORDINV)).SetClear(ClearScreen::Top)();
			Process::ReturnToHomeMenu();
			return;
		}

		auto languages = Language::getInstance()->listAvailableLanguages(PATH_LANGUAGE_BIN);
		if (languages.empty()) {
			MessageBox(Utils::Format("Error 578\nThe language.bin is empty or corrupted!\nGet more info and help on the Discord Server: %s\nGame will be closed now!", DISCORDINV)).SetClear(ClearScreen::Top)();
			Process::ReturnToHomeMenu();
			return;
		}

		bool languageExists = std::find(languages.begin(), languages.end(), language) != languages.end();

        if(!languageExists || SetInMenu) {
			// For first-time users, try to match the 3DS system language
			if (!languageExists && !SetInMenu) {
				const char* sysLang = SystemLanguageToShortName(System::GetSystemLanguage());
				if (sysLang && std::find(languages.begin(), languages.end(), std::string(sysLang)) != languages.end()) {
					language = sysLang;

					if (SetLanguage(language)) {
						languageExists = true;
					}
				}
			}

			if (!languageExists || SetInMenu) {
				std::vector<std::string> values;
				for (const auto& pair : languages) {
					values.push_back(pair.fullName);
				}

				Keyboard keyboard("Which language do you want to use?", values);
				keyboard.CanAbort(SetInMenu);

				int sel = keyboard.Open();
				if (sel < 0) {
					return;
				}

				if (sel < (int)languages.size()) {
					language = languages[sel].shortName;
				}

				if (!SetLanguage(language)) {
					MessageBox(Utils::Format("Error 608\nCouldn't save chosen language.\nGet more info and help on the Discord Server: %s", DISCORDINV)).SetClear(ClearScreen::Top)();
				}
				languageExists = true;
			}
        }

		if (!languageExists || !Language::getInstance()->loadFromBinary(PATH_LANGUAGE_BIN, language.c_str())) {
			MessageBox(Utils::Format("Error 605\nCouldn't load the language.\nGet more info and help on the Discord Server: %s", DISCORDINV)).SetClear(ClearScreen::Top)();

			DeleteLanguage();
			SetupLanguage(false); //redo language choosing
		}

		if (SetInMenu) {
			PluginMenu::UpdateLocalizedEntries();
			MessageBox("Successfully set new language!").SetClear(ClearScreen::Top)();
		}
    }
}