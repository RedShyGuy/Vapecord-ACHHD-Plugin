#pragma once

#include <CTRPluginFramework.hpp>

#pragma pack(push, 1)

namespace CTRPluginFramework {
    struct Item {
        u16 ID;
        u16 Flags;

        bool operator==(const Item& item) const {
            return ID == item.ID && Flags == item.Flags;
        }

        bool operator!=(const Item& item) const {
            return ID != item.ID || Flags != item.Flags;
        }

        bool operator>(const Item&item) const {
            return (ID + Flags) > (item.ID + item.Flags);
        }

        Item operator+(const u32& val) const {
            return Item(ID + val, Flags);
        }

        operator u32() const {
            return (Flags << 16) | (ID & 0xFFFF);
        }

        Item() {
            ID = 0;
            Flags = 0;
        }

        Item(const u32 &val) {
            ID = val;
            Flags = val >> 16;
        }

        Item(u16 v_ID, u16 v_Flags) {
            ID = v_ID;
            Flags = v_Flags;
        }
    public:
        std::string GetName(void);
        bool isValid(bool IsDropped = true);
    };
}

#pragma pack(pop)