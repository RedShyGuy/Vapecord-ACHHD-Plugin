#include <CTRPluginFramework.hpp>
#include "core/game_api/Item.hpp"

namespace CTRPluginFramework {
    bool Item::isValid(bool IsDropped) {
		return true;
	}

    std::string Item::GetName() {
        return "???";
    }
}