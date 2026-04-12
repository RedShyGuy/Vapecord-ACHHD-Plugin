#pragma once

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
	namespace MenuEntryId {
		// ID policy:
		// - IDs are append-only. Never renumber existing IDs.
		// - Menu order is independent from ID order.
		// - For new entries, just append a new ID at the end of the relevant group.
		// - Keep old IDs reserved when removing entries.
		constexpr u32 GroupSave = 0x01;
		constexpr u32 GroupMovement = 0x02;
		constexpr u32 GroupPlayerSave = 0x03;
		constexpr u32 GroupPlayer = 0x04;
		constexpr u32 GroupAnimation = 0x05;
		constexpr u32 GroupMisc = 0x06;
		constexpr u32 GroupDev = 0x07;
		constexpr u32 GroupPlugin = 0x08;

		constexpr u32 Make(u32 group, u32 index) {
			return (group << 16) | (index & 0xFFFF);
		}

		// Save folder
		constexpr u32 SaveBackupSettings = Make(GroupSave, 0x0001);

		// Movement folder
		constexpr u32 MovementWalkThroughWalls = Make(GroupMovement, 0x0001);
		constexpr u32 MovementRoomWarping = Make(GroupMovement, 0x0002);
		constexpr u32 MovementCoordMod = Make(GroupMovement, 0x0003);

		// PlayerSave folder
		constexpr u32 PlayerSaveRandomizer = Make(GroupPlayerSave, 0x0001);

		// Player folder
		//constexpr u32 PlayerRandomizer = Make(GroupPlayer, 0x0001);

		// Animation folder
		constexpr u32 AnimationSetAnimation = Make(GroupAnimation, 0x0001);
		constexpr u32 AnimationIdleAnimation = Make(GroupAnimation, 0x0002);
 
		// Misc folder
		constexpr u32 MiscPlayerInfo = Make(GroupMisc, 0x0001);
		constexpr u32 MiscInstantDrop = Make(GroupMisc, 0x0002);
		constexpr u32 MiscFastGameSpeed = Make(GroupMisc, 0x0003);

		// Dev folder
		constexpr u32 DevExecuteFunction = Make(GroupDev, 0x0001);

		// Plugin entries
		constexpr u32 PluginSettings = Make(GroupPlugin, 0x0001);
	}
}
