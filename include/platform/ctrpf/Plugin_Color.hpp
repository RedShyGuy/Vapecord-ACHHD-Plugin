#pragma once

#include <CTRPluginFramework.hpp>
#include "platform/ctrpf/FolderTypes.hpp"
#include "core/infrastructure/Address.hpp"

namespace CTRPluginFramework {
    #pragma pack(push, 1)
    struct ColorEntry {
		FolderType folderType;
		u8 r;
		u8 g;
		u8 b;
	};
    #pragma pack(pop)

    static const std::vector<ColorEntry> defaultColors = {
        { FolderType::Save, 0x78, 0x50, 0xC8 }, // Deep purple
        { FolderType::Movement, 0x3C, 0xC8, 0x64 }, // Green
        { FolderType::Player, 0x46, 0x82, 0xFF }, // Blue
        { FolderType::Animation, 0xFF, 0x5A, 0x96 }, // Pink
        { FolderType::Misc, 0x5A, 0x5A, 0x5A }, // Dark grey
        { FolderType::Dev, 0xFF, 0x1A, 0x69 }  // Vibrant red
    };

    void WriteCustomColors(const std::vector<ColorEntry>& colors);
    std::vector<ColorEntry> GetCustomColors();
    std::vector<ColorEntry> GetDefaultColors();
    bool CustomColorsExist();

	void EditColors();
}