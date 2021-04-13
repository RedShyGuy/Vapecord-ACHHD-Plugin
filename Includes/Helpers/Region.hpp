#ifndef REGION_HPP
#define REGION_HPP

#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework {
	enum CurrRegion {
        USA,
        EUR,
        JPN
    };

	extern CurrRegion c_Region;

	namespace Region {
		u32	AutoRegion(u32 usa, u32 eur, u32 jpn);
	}
}
#endif