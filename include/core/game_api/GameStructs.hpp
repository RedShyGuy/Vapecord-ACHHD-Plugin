#pragma once

#include <CTRPluginFramework.hpp>
#include "core/game_api/Item.hpp"

#define SAVESIZE 0x2BE940

#pragma pack(push, 1)

using EncVal = u64;

/*
Nanoseconds are used for time values in the save (not always).
They get calculated not by checking the elapsed time since 01.01.1970, but since 01.01.2000
*/
using Nanoseconds = u64;

namespace CTRPluginFramework {

    //4a0a48 might be save constructor
    //or 04a059c, looks more promising

    struct PlayerID { //0x16 //0x326A7490
        u16 PID;
        char16_t PlayerName[9];
        u8 Gender;
        u8 ZeroPad;

        bool operator==(const PlayerID& playerID) const {
            return PID == playerID.PID && 
                    std::equal(std::begin(PlayerName), std::end(PlayerName), std::begin(playerID.PlayerName)) && 
                    Gender == playerID.Gender && 
                    ZeroPad == playerID.ZeroPad;
        }

        std::string GetName() const {
            std::string out;
            Utils::ConvertUTF16ToUTF8(
                out,
                PlayerName
            );
            return out;
        }
    };

    struct TownID { //0x16
        u16 TID; //Default is 0
        char16_t DataTownName[9]; //Default is 0
        u8 Unknown01; //Default is 0xA
        u8 Unknown02;

        bool operator==(const TownID& townID) const {
            return TID == townID.TID && 
                    std::equal(std::begin(DataTownName), std::end(DataTownName), std::begin(townID.DataTownName)) && 
                    Unknown01 == townID.Unknown01 && 
                    Unknown02 == townID.Unknown02;
        }

        std::string GetName() const {
            std::string out;
            Utils::ConvertUTF16ToUTF8(
                out,
                DataTownName
            );
            return out;
        }
    };

    struct PersonalID { //Size: 0x2E
        PlayerID PlayerData;
        TownID TownData;
        u8 TPC_Country; //not sure if that is really that in hhd
        u8 TPC_County; //not sure if that is really that in hhd

        bool operator==(const PersonalID& personalID) const {
            return PlayerData == personalID.PlayerData && 
                    TownData == personalID.TownData && 
                    TPC_Country == personalID.TPC_Country && 
                    TPC_County == personalID.TPC_County;
        }
    };

    struct ACHHD_Pattern { //Size: 0x870
        char16_t Title[21];
        PersonalID CreatorData;
        u8 Palette[15];
        u8 UnusedChecksum = 1; //changing seems to have no effect //Default: 1, Set at 0x1B4F74 EUR 1.5
        u8 TenConstant; //seems to always be 0x0A
        u8 PatternType;
        u16 ZeroPad_2; //Zero Padding; Always 0x0000
        u8 PatternData1[512]; //mandatory

    //only used when PatternType < 0x09
        u8 PatternData2[512]; //optional
        u8 PatternData3[512]; //optional
        u8 PatternData4[512]; //optional
        u32 ZeroPad_3; //Zero Padding; Optional*/
    };

    //sizeof 0x6
    struct Player_Features {
        u8 HairStyle; //0xC
        u8 Tan; //0xD
        u8 HairColor; //0xE
        u8 EyeStyle; //0xF
        u8 EyeColor; //0x10
        u8 padding; //0x11 //probably padding
    };

    struct Player_Outfit { //sizeof = 0x1C
        Item Hat; //0x12
        Item Accessory; //0x16
        Item TopWear; //0x1A
        Item BottomWear; //0x1E
        Item Socks; //0x22
        Item Shoes; //0x26
        Item HeldItem; //0x2A
    };

    //sizeof: 0x1090
    struct UnknownStruct2 {
        u8 unk[0x1090];
    };

    //set in 0x1f93a0
    //sizeof: 0x1B3CD4
    struct UnknownStruct3 {
        UnknownStruct2 unkStruct[420]; //0x40 (size: 0x1B2C40)
        UnknownStruct2 unk28; //0x1B2C80
        u32 unk3; //0x1B3D10 u32 //ctor sets 0xFFFFFFFF
    };

    //sizeof: 0x1138
    struct UnknownStruct5 {
        u8 unk[0x1138];
    };

    //set at 0x2133b8
    //sizeof: 0xBD6C
    struct UnknownStruct6 {
        UnknownStruct5 unkStruct[10]; //0x1B3D18
        UnknownStruct5 unk1; //0x1BE948
        u32 unk2; //0x1BFA80 u32 //ctor sets 0xFFFFFFFF
    };

    //sizeof: 0x78
    struct UnknownStruct7 {
        u8 unk26[0x78];
    };

    static constexpr u8 EmoticonsList[48] = {
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
		0x0C, 0x0D, 0x0E, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x20, 0x21, 0x24, 0x26,
		0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2E, 0x2F, 0x30, 0x31, 0x32,
		0x46, 0x47, 0x48, 0x4A
	};

    //0x16
    struct Player_Flags {
    //Offset: 0x326A74A6
        u8 unkFlag1 : 1; //0x01
        u8 unkFlag2 : 1; //0x02
        u8 unkFlag3 : 1; //0x04
        u8 unkFlag4 : 1; //0x08
        u8 unkFlag5 : 1; //0x10
        u8 unkFlag6 : 1; //0x20
        u8 unkFlag7 : 1; //0x40
        u8 unkFlag8 : 1; //0x80 //set to 1 after finishing first client
    //Offset: 0x326A74A7
        u8 unkFlag9 : 1; //0x01 //maybe furniture tutorial finished? after slideshow
        u8 unkFlag10 : 1; //0x02
        u8 unkFlag11 : 1; //0x04
        u8 unkFlag12 : 1; //0x08
        u8 unkFlag13 : 1; //0x10 //daily report introduction
        u8 unkFlag14 : 1; //0x20
        u8 unkFlag15 : 1; //0x40
        u8 unkFlag16 : 1; //0x80
    //Offset: 0x326A74A8
        u8 unkFlag17 : 1; //0x01 //maybe furniture tutorial finished? when talking to lottie after tutorial
        u8 unkFlag18 : 1; //0x02 //house finished? (goes back to 0 after leaving the house)
        u8 unkFlag19 : 1; //0x04
        u8 unkFlag20 : 1; //0x08
        u8 unkFlag21 : 1; //0x10
        u8 unkFlag22 : 1; //0x20
        u8 unkFlag23 : 1; //0x40
        u8 unkFlag24 : 1; //0x80
    //Offset: 0x326A74A9
        u8 unkFlag25 : 1; //0x01
        u8 unkFlag26 : 1; //0x02 //maybe trash can or rotate or client info
        u8 unkFlag27 : 1; //0x04 //probably unlocked leaf icon (furniture list)
        u8 unkFlag28 : 1; //0x08 //maybe trash can or rotate or client info
        u8 unkFlag29 : 1; //0x10 //unlocked wall decorations icon
        u8 unkFlag30 : 1; //0x20 //unlocked wallpaper/floors icon
        u8 unkFlag31 : 1; //0x40 //search items icon
        u8 unkFlag32 : 1; //0x80
    //Offset: 0x326A74AA
        u8 unkFlag33 : 1; //0x01
        u8 unkFlag34 : 1; //0x02
        u8 unkFlag35 : 1; //0x04
        u8 unkFlag36 : 1; //0x08 //unlocked rugs icon
        u8 unkFlag37 : 1; //0x10
        u8 unkFlag38 : 1; //0x20
        u8 InviteAmiiboToClientIntroduction : 1; //0x40
        u8 unkFlag40 : 1; //0x80
    //Offset: 0x326A74AB
        u8 unkFlag41 : 1; //0x01
        u8 unkFlag42 : 1; //0x02
        u8 unkFlag43 : 1; //0x04
        u8 unkFlag44 : 1; //0x08
        u8 unkFlag45 : 1; //0x10 //set to 1 after arriving in office after first client
        u8 unkFlag46 : 1; //0x20
        u8 unkFlag47 : 1; //0x40
        u8 unkFlag48 : 1; //0x80
    //Offset: 0x326A74AC
        u8 unkFlag49 : 1; //0x01
        u8 unkFlag50 : 1; //0x02
        u8 unkFlag51 : 1; //0x04
        u8 ClientListUnlocked : 1; //0x08
        u8 unkFlag53 : 1; //0x10 //visited client?
        u8 unkFlag54 : 1; //0x20
        u8 unkFlag55 : 1; //0x40 //after lyle tells you to go outside and talk to possible clients
        u8 unkFlag56 : 1; //0x80 //set to 1 after finishing second client
    //Offset: 0x326A74AD
        u8 unkFlag57 : 1; //0x01
        u8 unkFlag58 : 1; //0x02 //set to 1 after finishing first&second client (0 when day is over)
        u8 unkFlag59 : 1; //0x04
        u8 unkFlag60 : 1; //0x08
        u8 unkFlag61 : 1; //0x10
        u8 unkFlag62 : 1; //0x20
        u8 unkFlag63 : 1; //0x40
        u8 unkFlag64 : 1; //0x80
    //Offset: 0x326A74AE
        u8 unkFlag65 : 1; //0x01
        u8 unkFlag66 : 1; //0x02
        u8 unkFlag67 : 1; //0x04
        u8 unkFlag68 : 1; //0x08
        u8 unkFlag69 : 1; //0x10
        u8 unkFlag70 : 1; //0x20
        u8 unkFlag71 : 1; //0x40
        u8 unkFlag72 : 1; //0x80
    //Offset: 0x326A74AF
        u8 GameplayDataSettingsIntroduction : 1; //0x01
        u8 SendGameplayData : 1; //0x02
        u8 unkFlag75 : 1; //0x04
        u8 unkFlag76 : 1; //0x08
        u8 unkFlag77 : 1; //0x10 //Maybe has study book unlocked? (Ceiling Decor & Refurbishing unlocked)
        u8 CustomDesignsUnlocked : 1; //0x20
        u8 EvenMoreDesignsUnlocked : 1; //0x40
        u8 WindowsAndMoreUnlocked : 1; //0x80
    //Offset: 0x326A74B0
        u8 SoundSceneryUnlocked : 1; //0x01
        u8 RefurbishingUnlocked : 1; //0x02
        u8 HappyHomeCameraUnlocked : 1; //0x04
        u8 WorldInsectsUnlocked : 1; //0x08
        u8 WorldFishUnlocked : 1; //0x10
        u8 AncientFossilsUnlocked : 1; //0x20
        u8 GyroidsUnlocked : 1; //0x40
        u8 ArtCollectionUnlocked : 1; //0x80
    //Offset: 0x326A74B1
        u8 unkFlag89 : 1; //0x01
        u8 StylingMachineUnlocked : 1; //0x02
        u8 unkFlag91 : 1; //0x04
        u8 unkFlag92 : 1; //0x08
        u8 unkFlag93 : 1; //0x10
        u8 unkFlag94 : 1; //0x20 //second day over?
        u8 unkFlag95 : 1; //0x40
        u8 unkFlag96 : 1; //0x80
    //Offset: 0x326A74B2
        u8 unkFlag97 : 1; //0x01
        u8 unkFlag98 : 1; //0x02
        u8 unkFlag99 : 1; //0x04
        u8 unkFlag100 : 1; //0x08
        u8 unkFlag101 : 1; //0x10
        u8 unkFlag102 : 1; //0x20
        u8 unkFlag103 : 1; //0x40
        u8 unkFlag104 : 1; //0x80
    //Offset: 0x326A74B3
        u8 unkFlag105 : 1; //0x01
        u8 unkFlag106 : 1; //0x02
        u8 unkFlag107 : 1; //0x04
        u8 unkFlag108 : 1; //0x08
        u8 unkFlag109 : 1; //0x10
        u8 unkFlag110 : 1; //0x20
        u8 unkFlag111 : 1; //0x40
        u8 unkFlag112 : 1; //0x80
    //Offset: 0x326A74B4
        u8 unkFlag113 : 1; //0x01
        u8 unkFlag114 : 1; //0x02
        u8 unkFlag115 : 1; //0x04
        u8 unkFlag116 : 1; //0x08
        u8 unkFlag117 : 1; //0x10
        u8 unkFlag118 : 1; //0x20
        u8 unkFlag119 : 1; //0x40
        u8 unkFlag120 : 1; //0x80
    //Offset: 0x326A74B5
        u8 unkFlag121 : 1; //0x01
        u8 unkFlag122 : 1; //0x02
        u8 unkFlag123 : 1; //0x04
        u8 unkFlag124 : 1; //0x08
        u8 unkFlag125 : 1; //0x10
        u8 unkFlag126 : 1; //0x20
        u8 unkFlag127 : 1; //0x40
        u8 unkFlag128 : 1; //0x80
    //Offset: 0x326A74B6
        u8 unkFlag129 : 1; //0x01
        u8 unkFlag130 : 1; //0x02
        u8 unkFlag131 : 1; //0x04
        u8 unkFlag132 : 1; //0x08
        u8 unkFlag133 : 1; //0x10
        u8 unkFlag134 : 1; //0x20
        u8 unkFlag135 : 1; //0x40
        u8 unkFlag136 : 1; //0x80
    //Offset: 0x326A74B7
        u8 unkFlag137 : 1; //0x01
        u8 hasStudiedLessonToday : 1; //0x02
        u8 unkFlag139 : 1; //0x04
        u8 SearchItemsIntroduction : 1; //0x08
        u8 unkFlag141 : 1; //0x10
        u8 EmoticonsUnlocked : 1; //0x20
        u8 unkFlag143 : 1; //0x40
        u8 unkFlag144 : 1; //0x80
    //Offset: 0x326A74B8
        u8 unkFlag145 : 1; //0x01
        u8 unkFlag146 : 1; //0x02
        u8 unkFlag147 : 1; //0x04
        u8 unkFlag148 : 1; //0x08
        u8 unkFlag149 : 1; //0x10
        u8 unkFlag150 : 1; //0x20
        u8 unkFlag151 : 1; //0x40
        u8 unkFlag152 : 1; //0x80
    //Offset: 0x326A74B9
        u8 unkFlag153 : 1; //0x01
        u8 unkFlag154 : 1; //0x02
        u8 unkFlag155 : 1; //0x04
        u8 unkFlag156 : 1; //0x08
        u8 unkFlag157 : 1; //0x10
        u8 unkFlag158 : 1; //0x20
        u8 unkFlag159 : 1; //0x40 //1 if day is going, 0 if day is over ?
        u8 unkFlag160 : 1; //0x80
    //Offset: 0x326A74BA
        u8 unkFlag161 : 1; //0x01
        u8 unkFlag162 : 1; //0x02
        u8 unkFlag163 : 1; //0x04
        u8 unkFlag164 : 1; //0x08
        u8 unkFlag165 : 1; //0x10
        u8 unkFlag166 : 1; //0x20
        u8 unkFlag167 : 1; //0x40
        u8 unkFlag168 : 1; //0x80
    //Offset: 0x326A74BB
        u8 unkFlag169 : 1; //0x01
        u8 unkFlag170 : 1; //0x02
        u8 unkFlag171 : 1; //0x04
        u8 unkFlag172 : 1; //0x08
        u8 unkFlag173 : 1; //0x10
        u8 unkFlag174 : 1; //0x20
        u8 unkFlag175 : 1; //0x40
        u8 unkFlag176 : 1; //0x80
    };

    /*
    Ceiling Decor
    Custom Designs
    Even More Designs
    Windows And More
    Sound Scenery
    */

    //sizeof: 0x40DA0
    struct ACHHD_Player {
        u8 unk8[0xC]; //0x1BFA88 some struct data (at 0x49BBD0)
        Player_Features features; //0x1BFA94
        Player_Outfit outfit; //0x1BFA9A
        u8 unkD; //0x1BFAB6
        u8 paddingMaybe; //0x1BFAB7
        ACHHD_Pattern patterns[120]; //0x1BFAB8 (size: 0x3F480)
        u8 unk9[0x78]; //0x1FEF38
        PlayerID playerInfo; //0x1FEFB0

        Player_Flags flags; //0x1FEFC6 //idk if it starts here, maybe

        u8 unkB[0x17C4]; //0x1FEFDC ?
        Item UnknownItems1[15]; //0x2007A0
        u8 Emoticons[48]; //0x2007DC
        u8 unkC[0x1C]; //0x20080C ?
    };

    //sizeof: 0x15
    struct UnknownStruct8 {
        u16 unk1; //0x24
        u32 unk2; //0x26
        u32 unk3; //0x2A
        u32 unk4; //0x2E
        u32 unk5; //0x32
        u16 unk6; //0x36
        u8 unk7; //0x38
    };

    //At 0x1A0
    //sizeof: 0x2BE780 (Probably)
    struct ACHHD_Data {
        u32 Checksum; //0x0 maybe checksum
        u8 unk27[2]; //0x5
        u8 unk1; //0x6
        u8 unk2[5]; //0x7

        u8 unk29[0x18]; //0xC
        UnknownStruct8 unkStruct8; //0x24 (size: 0x15)

        u8 unk30[7]; //0x39
        UnknownStruct3 unkStruct3; //0x40 (size: 0x1B2C40)

        u8 unk4[4]; //0x1B3D14 ?
        UnknownStruct6 unkStruct6; //0x1B3D18 (size: 0xBD6C)
        
        u8 unk7[4]; //0x1BFA84 ?
        ACHHD_Player player; //0x1BFA88

        u8 unkC[4]; //0x200828 ?
        
        u8 unkD[0x13B4]; //0x20082C might be a struct
        u8 unkE[0x4868]; //0x201be0 might be a struct (at 0x17d974)
        u8 unkF[0x4E8]; //0x206448 might be a struct (at 0x1a6378)
        u8 unk10[0x308]; //0x206930 might be a struct (at 0x17d5e0)
        u8 unk11[0x7800]; //0x206C38 ? should be correct size of it
        u32 unk12; //0x20E438 u32
        u8 unk13[0xAF55C]; //0x20E43C ?
        u8 unk14[8]; //0x2BD998 ?
        u8 unk15; //0x2BD9A0 u8
        u8 unk16; //0x2BD9A1
        u8 unk17[4]; //0x2BD9A2 ?
        u8 unk18; //0x2BD9A6 u8
        u8 unk19; //0x2BD9A7
        u8 unk1A[0x10]; //0x2BD9A8 ?
        u8 unk1B; //0x2BD9B8 u8
        u8 unk1C; //0x2BD9B9 u8
        u8 unk1D[0xE]; //0x2BD9BA
        u8 unk1E; //0x2BD9C8 u8
        u8 unk1F; //0x2BD9C9 u8
        u8 unk20[2]; //0x2BD9CA
        u8 unk21[0xC80]; //0x2BD9CC might be a struct (0x1A67B8)
        u32 unk22; //0x2BE64C u32
        u8 unk23[0x90]; //0x2BE648 might be a struct (at 0x545854)
        u32 unk2B; //0x2BE6E0 u32
        u32 unk2A; //0x2BE6E4 u32
        u32 unk24; //0x2BE6E8 u32
        u32 unk25; //0x2BE6EC u32
        UnknownStruct7 unkStruct7; //0x2BE6F0
        u8 unk2C[0x18]; //0x2BE768
    };

    //sizeof: 0xE
    struct UnknownStruct0 {
        u32 unk0;
        u32 unk1;
        u32 unk2;
        u16 unk3;
    };

    //Data: 0x324A8340 -> 0x32766C80
    //sizeof: 0x2BE940
    struct TakumiData {
        u32 unk0; //0x0 always 0xFFFFFFFF i think
        u8 unk1[0x19C]; //0x4 really not sure, all 0 currently for me
        ACHHD_Data data; //0x1A0
        UnknownStruct0 unkStruct; //0x2BE920 some struct
        u8 unk2[0x12]; //0x2BE92A
    };
}

#pragma pack(pop)
