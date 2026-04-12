#include "core/Config.hpp"
#include "core/infrastructure/PluginUtils.hpp"
#include "features/cheats.hpp"
#include "platform/ctrpf/Plugin_Color.hpp"
#include "core/infrastructure/Language.hpp"
#include "Files.h"

namespace CTRPluginFramework {
	void pluginSettingsEntry(MenuEntry *entry) {
		const std::vector<std::string> settingsOptions = {
			Language::getInstance()->get(TextID::CHANGE_LANGUAGE),
			Language::getInstance()->get(TextID::CHANGE_MENU_COLORS)
		};

		Keyboard keyboard(Language::getInstance()->get(TextID::PLUGIN_SETTINGS), settingsOptions);
		int choice = keyboard.Open();
		if (choice < 0) {
			return;
		}

		switch (choice) {
			case 0:
				Config::SetupLanguage(true);
				break;
			case 1:
				EditColors();
				break;
			default:
				break;
		}
	}
}