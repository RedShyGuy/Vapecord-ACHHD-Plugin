#pragma once

#include <CTRPluginFramework.hpp>
#include "core/game_api/Item.hpp"

#pragma pack(push, 1)

typedef char16_t wchar; ///< Wide character type
using EncVal = u64;

/*
Nanoseconds are used for time values in the save (not always).
They get calculated not by checking the elapsed time since 01.01.1970, but since 01.01.2000
*/
using Nanoseconds = u64;

namespace CTRPluginFramework {
    
}

#pragma pack(pop)
