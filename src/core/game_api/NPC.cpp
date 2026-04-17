#include <CTRPluginFramework.hpp>
#include "core/game_api/NPC.hpp"
#include "core/infrastructure/Address.hpp"

namespace CTRPluginFramework {
    std::string NPC::GetNName(u16 VID) {
		static Address SetUp(0x582F1C);
		static Address NNPCModelGet(0x4786B8);

		u32 Stack[44];
		u32 add = Address(0x621690).Call<u32>(Stack);

		u32 npcModel = NNPCModelGet.Call<u32>(VID);
		SetUp.Call<void>(*(u32 *)Address(0x738C54).addr, add, (char *)"STR_NNpc_name", npcModel);

		std::string NNPCName = "";
		Process::ReadString(Stack[1], NNPCName, 0x20, StringFormat::Utf16);
		return NNPCName.empty() ? "???" : NNPCName;
	}

	std::string NPC::GetSPName(u16 SPVID) {
		static Address SetUp(0x582F1C);
        static Address NNPCModelGet(0x4786B8);

		u32 Stack[44];
		u32 add = Address(0x621690).Call<u32>(Stack);

        u32 npcModel = NNPCModelGet.Call<u32>(SPVID);
		SetUp.Call<void>(*(u32 *)Address(0x738C54).addr, add, (char *)"STR_SPNpc_name", npcModel);

		std::string SPNPCName = "";
		Process::ReadString(Stack[1], SPNPCName, 0x20, StringFormat::Utf16);
		return SPNPCName.empty() ? "???" : SPNPCName;
	}

	bool NPC::PopulateAmiibo(SpecieID specieID, std::vector<std::string> &vec, std::vector<PACKED_AmiiboInfo> &info) {
		if(specieID >= (SpecieID)0) {
			vec.clear();
			info.clear();

			for(const AmiiboConfigList& amiibo : amiiboVillagers) {
				if(amiibo.Species == specieID) {
                    std::string Name;

                    if (amiibo.Species == SpecieID::Special) {
                        if ((amiibo.amiiboId & 0xFFFFFF00) == 0x18400) {
                            Name = "Timmy&Tommy";
                        } else {
                            Name = GetSPName(amiibo.VID);
                        }
                    } else {
                        Name = GetNName(amiibo.VID);
                    }
					info.push_back(PACKED_AmiiboInfo{Name, amiibo});
					vec.push_back(Name);
				}
			}
			return true;
		}
		return false;
	}

	void NPC::PopulateRace(std::vector<std::string> &vec) {
		vec.clear();

        vec.push_back("Anteater");
        vec.push_back("Bear");
        vec.push_back("Bird");
        vec.push_back("Bull");
        vec.push_back("Cat");
        vec.push_back("Bearcub");
        vec.push_back("Chicken");
        vec.push_back("Cow");
        vec.push_back("Alligator");
        vec.push_back("Deer");
        vec.push_back("Dog");
        vec.push_back("Duck");
        vec.push_back("Elephant");
        vec.push_back("Frog");
        vec.push_back("Goat");
        vec.push_back("Gorilla");
        vec.push_back("Hamster");
        vec.push_back("Hippo");
        vec.push_back("Horse");
        vec.push_back("Koala");
        vec.push_back("Kangaroo");
        vec.push_back("Lion");
        vec.push_back("Monkey");
        vec.push_back("Mouse");
        vec.push_back("Octopus");
        vec.push_back("Ostrich");
        vec.push_back("Eagle");
        vec.push_back("Penguin");

        vec.push_back("Pig");
        vec.push_back("Rabbit");
        vec.push_back("Rhinocero");
        vec.push_back("Sheep");

        vec.push_back("Squirrel");
        vec.push_back("Tiger");
        vec.push_back("Wolf");
		vec.push_back("Special");
	}
}