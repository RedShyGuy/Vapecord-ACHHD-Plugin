#include "cheats.hpp"
#include "CTRPluginFramework.hpp"
#include "GameHelper.hpp"

namespace CTRPluginFramework
{
	volatile u32(*pfunction0)();
	volatile u32(*pfunction1)(u32 param1);
	volatile u32(*pfunction2)(u32 param1, u32 param2);
	volatile u32(*pfunction3)(u32 param1, u32 param2, u32 param3);
	volatile u32(*pfunction4)(u32 param1, u32 param2, u32 param3, u32 param4);
	volatile u32(*pfunction5)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
	volatile u32(*pfunction6)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
	volatile u32(*pfunction7)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
	volatile u32(*pfunction8)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
	volatile u32(*pfunction9)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9);
	volatile u32(*pfunction10)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10);
	volatile u32(*pfunction11)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10, u32 param11);
	
	const u64 USA = 0x000400000014F100; 
	const u64 EUR = 0x000400000014F200;
	const u64 JPN = 0x000400000014F000;
	
	int Region::AutoRegion(u32 usa, u32 eur, u32 jpn) {
		switch (Process::GetTitleID()) {
		case USA: return(usa);  
		case EUR: return(eur); 
		case JPN: return(jpn);
		}
	}
	
	u32 GameHelper::ExecuteAnimation(u8 animID) {
		Process::Write32((u32)&pfunction4, 0x4D8960);
		return pfunction4(0x336729B0, animID, 0x336730BC, 0);
	}
	
	u32 GameHelper::GetPInstance() {
		return *(u32 *)0x847D80;
	}
	
	u8 GameHelper::GetCurrentAnim() {
		if(Outside()) return *(u8 *)0x33673AC8;
		else return *(u8 *)0x336730C0;
	}
	
	float GameHelper::GetCoordinates() {
		if(Outside()) return *(float *)0x33673408;
		else return *(float *)0x33672A00;
	}
	
	bool GameHelper::Outside() {
		if(*(u32 *)0x33672A00 != 0) return true;
		else return false;
	}
	
	u32 GameHelper::RoomChange(u8 room) {
		Process::Write32((u32)&pfunction4, 0x496F5C);
		return pfunction4(room, 1, 1, 0);
	}
}