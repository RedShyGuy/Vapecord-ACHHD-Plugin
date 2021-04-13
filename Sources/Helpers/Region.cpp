#include "cheats.hpp"

namespace CTRPluginFramework {
	CurrRegion c_Region = USA;

	u32 Region::AutoRegion(u32 usa, u32 eur, u32 jpn) {
		switch(c_Region) {
			default: return 0;
			case CurrRegion::USA: return(usa);
			case CurrRegion::EUR: return(eur);
			case CurrRegion::JPN: return(jpn);
		}
	}
}