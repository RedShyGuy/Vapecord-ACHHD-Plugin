#pragma once

#include <CTRPluginFramework.hpp>
//#include "core/game_api/GameStructs.hpp"

namespace CTRPluginFramework {
	struct ID_U8Data {
		const char* Name; //name of ID
		u8 ID; //ID
	};
	
	struct Range {
		u32 start;
		u32 end;
	};

	class KeyRange {
		public:
			static void Set(Range range) {
				sRange = range;
			}
			static Range Get(void) {
				return sRange;
			}

			static Range sRange;
	};

	enum class SpecieID : u8 {
		Anteater = 0, Bear, Bird, Bull,
		Cat, Bearcub, Chicken, Cow,
		Alligator, Deer, Dog, Duck,
		Elephant, Frog, Goat, Gorilla,
		Hamster, Hippo, Horse, Koala,
		Kangaroo, Lion, Monkey, Mouse,
		Octopus, Ostrich, Eagle, Penguin,
		Pig, Rabbit, Rhinocero, Sheep,
		Squirrel, Tiger, Wolf,
		Special,
	};

	typedef struct {
        u32 amiiboId; // (bswap16(characterId) << 8) | characterVariant
        u8 amiiboSeries;
        u16 modelNumber;
		u16 VID; //VID for name lookup
		SpecieID Species; //ID of NPC's species to differentiate NPCs
    } AmiiboConfigList;

	typedef struct {
		u16 lastwritedate_year;
		u8 lastwritedate_month;
		u8 lastwritedate_day;
		u16 write_counter;
		u16 characterId;
		u8 characterVariant;
		u8 amiiboSeries;
		u16 modelNumber;
		u8 amiiboType;
		u8 version;/// "This is byte[3] from NFC page[0x4]."
		u8 appdata_size;/// "NFC module writes hard-coded u8 value 0xD8 here. This is the size of the Amiibo AppData, apps can use this with the AppData R/W commands. ..."
		u8 reserved[0x31];/// "Unused / reserved: this is cleared by NFC module but never written after that."
	} NFC_AmiiboConfig;

	typedef enum {
		NFC_TagState_Uninitialized = 0, /// nfcInit() was not used yet.
		NFC_TagState_ScanningStopped = 1, /// Not currently scanning for NFC tags. Set by nfcStopScanning() and nfcInit(), when successful.
		NFC_TagState_Scanning = 2, /// Currently scanning for NFC tags. Set by nfcStartScanning() when successful.
		NFC_TagState_InRange = 3, /// NFC tag is in range. The state automatically changes to this when the state was previously value 2, without using any NFC service commands.
		NFC_TagState_OutOfRange = 4, /// NFC tag is now out of range, where the NFC tag was previously in range. This occurs automatically without using any NFC service commands. Once this state is entered, it won't automatically change to anything else when the tag is moved in range again. Hence, if you want to keep doing tag scanning after this, you must stop+start scanning.
		NFC_TagState_DataReady = 5 /// NFC tag data was successfully loaded. This is set by nfcLoadAmiiboData() when successful.
	} NFC_TagState;

	struct PACKED_AmiiboInfo {
		std::string Name;
		AmiiboConfigList amiiboConfig;
	};

	void ValidKeyboardCheck(Keyboard& keyboard, KeyboardEvent& event);
	void ItemChange(Keyboard& keyboard, KeyboardEvent& event);
	void TextItemChange(Keyboard& keyboard, KeyboardEvent& event);
	
    extern const AmiiboConfigList amiiboVillagers[394];

	namespace IDChecks {
		bool		StageValid(u8 stageID);
		bool		AnimationValid(u8 animID, u8 playerIndex = 4);
		bool		SnakeValid(u16 snakeID);
		bool		EmotionValid(u8 emotionID);
		std::string	GetStageName(u8 ID);
		bool		IsInRange(u16 ID, u16 startID, u16 endID);
	}
}