#pragma once

#include <CTRPluginFramework.hpp>
#include "core/checks/IDChecks.hpp"
#include "core/game_api/GameStructs.hpp"

namespace CTRPluginFramework {
  namespace NPC {
      std::string GetNName(u16 VID);
      std::string GetSPName(u16 SPVID);
      bool PopulateAmiibo(SpecieID specieID, std::vector<std::string> &vec, std::vector<PACKED_AmiiboInfo> &info);
      void PopulateRace(std::vector<std::string> &vec);
  }
}