#include <CTRPluginFramework.hpp>
#include <csvc.h>
#include "core/RuntimeContext.hpp"
#include "features/cheats.hpp"
#include "core/game_api/Game.hpp"
#include "core/game_api/Animation.hpp"

namespace CTRPluginFramework {
//This patch the NFC disabling the touchscreen when scanning an amiibo, which prevents ctrpf to be used
    static void    ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalRoundedSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalRoundedSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if(R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalRoundedSize, static_cast<MapExFlags>(0))))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalRoundedSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalRoundedSize);
	exit:
        svcCloseHandle(processHandle);
    }

    void ToolFix(void) {
		//this here gives the umbrella 0x3277 the correct data and lets the player use it correctly
		u32 i = Game::GetAcPlayerInstance();
		if(i == 0)
			return;
		
		u16 currentTool = *(u16 *)(i + 0x7A4);
		
		//tool unequip
		if(currentTool != 0x7FFE && Controller::IsKeyPressed(Key::DPadDown) && Animation::GetCurrentAnim() == 3) {
			Animation::AnimationWrapper(0x44, 0, 0, 0, 0);
		}
		//If tool is umbrella and player spins it
		if(currentTool == 0x3277 && Controller::IsKeyPressed(Key::A) && Animation::GetCurrentAnim() == 3) {
			Animation::AnimationWrapper(0x5F, 0, 0, 0, 0);
		}
		//if tool is popper, player can pop it
		if(currentTool == 0x3247 && Controller::IsKeyPressed(Key::A) && Animation::GetCurrentAnim() == 3) {
			Animation::AnimationWrapper(0x60, 0, 0, 0, 0);
		}
	}
	
	//very neccessary lol 
	void UmbrellaSecretEquip(void) {
		if(Game::GetStageID() != 0xA)
			return;
		
		u32 i = Game::GetAcPlayerInstance();
		if(i == 0)
			return;
		
		u16 currentTool = *(u16 *)(i + 0x7A4);
		if(currentTool != 0x7FFE)
			return;
		
		Game::WorldCoord worldCoords = Game::GetWorldCoords();
		if(worldCoords.wX != 0xF || worldCoords.wY != 0xC)
			return;
		
		if(!Controller::IsKeyPressed(Key::A))
			return;
		
		if(Animation::GetCurrentAnim() != 0x48)
			return;
		
		Animation::AnimationWrapper(0x43, 0, 0x3277, 0, 0);
	}

//FwkSettings Patch Process/Gets called even if the game is not supported
	void PatchProcess(FwkSettings &settings) {
		ToggleTouchscreenForceOn();
		settings.ThreadPriority = 0x30;

		settings.CachedDrawMode = true;

    //This hopefully fixes issues with wumiibo on old 3ds'
        if (!System::IsNew3DS()) {
            settings.UseGameHidMemory = true;
        }
	}

    void OnExitProcess(void) {
        ToggleTouchscreenForceOn();
    }
}