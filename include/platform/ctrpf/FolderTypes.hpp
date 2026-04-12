#pragma once

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
    enum class FolderType : u8 {
        Save = 0,
        Movement,
        Player,
        Animation,
        Misc,
        Dev,
        None
    };

    enum class SubFolder : u8 {
        PlayerSave = 0,
        None
    };
}