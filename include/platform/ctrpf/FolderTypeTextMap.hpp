#pragma once

#include "platform/ctrpf/FolderTypes.hpp"
#include "core/infrastructure/TextID.hpp"

namespace CTRPluginFramework {
    inline TextID GetFolderTextId(FolderType type) {
        switch (type) {
            case FolderType::Save:        return TextID::SAVE_CODES;
            case FolderType::Movement:    return TextID::MOVEMENT_CODES;
            case FolderType::Player:      return TextID::PLAYER_CODES;
            case FolderType::Animation:   return TextID::ANIMATION_CODES;
            case FolderType::Misc:        return TextID::MISC_CODES;
            case FolderType::Dev:         return TextID::DEV_CODES;
            default:                      return TextID::NONE;
        }
    }

    inline TextID GetFolderNoteTextId(FolderType type) {
        switch (type) {
            case FolderType::Save:        return TextID::SAVE_CODES_NOTE;
            case FolderType::Movement:    return TextID::MOVEMENT_CODES_NOTE;
            case FolderType::Player:      return TextID::PLAYER_CODES_NOTE;
            case FolderType::Animation:   return TextID::ANIMATION_CODES_NOTE;
            case FolderType::Misc:        return TextID::MISC_CODES_NOTE;
            case FolderType::Dev:         return TextID::DEV_CODES_NOTE;
            default:                      return TextID::NONE;
        }
    }

    inline TextID GetSubFolderTextId(FolderType parent, SubFolder sub) {
        if (sub == SubFolder::None)
            return TextID::NONE;

        switch (parent) {
            case FolderType::Player:
                if (sub == SubFolder::PlayerSave)
                    return TextID::PLAYER_SAVE_CODES;
                break;

            default:
                break;
        }

        return TextID::NONE;
    }

    inline TextID GetSubFolderNoteTextId(FolderType parent, SubFolder sub) {
        if (sub == SubFolder::None)
            return TextID::NONE;

        switch (parent) {
            case FolderType::Player:
                if (sub == SubFolder::PlayerSave)
                    return TextID::PLAYER_SAVE_CODES_NOTE;
                break;

            default:
                break;
        }

        return TextID::NONE;
    }
}
