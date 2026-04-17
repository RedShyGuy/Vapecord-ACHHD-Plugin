#include <CTRPluginFramework.hpp>
#include "core/infrastructure/Language.hpp"
#include "core/infrastructure/Address.hpp"
#include "core/checks/IDChecks.hpp"
#include "core/game_api/NPC.hpp"

namespace CTRPluginFramework {
    PACKED_AmiiboInfo amiibo;
    bool cancelled = false;

    int AmiiboStateMachine_Hook(int context) {
        static Address getAmiiboModelData(0x5728A4);
        static Address loadAmiiboData(0x5036E0);
        static Address flip(0x11E144); //Idk, chooses wether to use timmy or tommy

        u8 state = *(u8*)(context + 0x8B0);
    //Idle, cleanup, spawn states -> let original handle
        if (state == 0 || state >= 15) {
            HookContext& ctx = HookContext::GetCurrent();
            return ctx.OriginalFunction<int, int>(context);
        }

        if (cancelled) { //If user cancelled, set state to cleanup
            *(u8*)(context + 0x8B0) = 15;
            *(u8*)(context + 0x8B1) = 2;
            return 0;
        }

        u32* res = getAmiiboModelData.Call<u32*>(&amiibo.amiiboConfig.amiiboId);

        u16 vid = amiibo.amiiboConfig.VID;

    //If timmy&tommy
        if ((amiibo.amiiboConfig.amiiboId & 0xFFFFFF00) == 0x18400) {
            if (flip.Call<u32>(2) == 0) {
                vid = 0x166; //timmy
            }
            else {
                vid = 0x167; //tommy
            }
        }

        *(u16*)(context + 0x898) = vid;
        *(u32*)(context + 0x89C) = (u32)res + 6;
        *(u8*)(context + 0x8B3) = amiibo.amiiboConfig.amiiboId & 0xFF;
        *(u8*)(context + 0x8B1) = 1; //success
        *(u8*)(context + 0x8B0) = 0;

        if (*(u8*)(context + 0x8AF) == 1) {
            *(u32*)(context + 0x798) = 0;
            if (loadAmiiboData.Call<int>(vid, *(u32*)(context + 0x89C))) {
                *(u8*)(context + 0x8B0) = 16;
                *(u8*)(context + 0x8A9) |= 0x20;
                return 0;
            }
            *(u8*)(context + 0x8B1) = 15;
        }

        return 0;
    }

    s32 SelectAmiibo(void* arg) {
        cancelled = false;

        Process::Pause();

        Keyboard keyboard(Language::getInstance()->get(TextID::AMIIBO_SPOOFER_SPECIES));

        std::vector<std::string> keyVec;
        NPC::PopulateRace(keyVec);
        keyboard.Populate(keyVec);

        int res = keyboard.Open(); //Pick a species
        if(res >= 0) {
            keyboard.GetMessage() = Language::getInstance()->get(TextID::AMIIBO_SPOOFER_VILLAGER);
            keyVec.clear();

            std::vector<PACKED_AmiiboInfo> amiiboVec;
            NPC::PopulateAmiibo((SpecieID)res, keyVec, amiiboVec);
            keyboard.Populate(keyVec);

            res = keyboard.Open(); //Pick villager based on species
            if(res >= 0) { //User picked a specific villager
                amiibo = amiiboVec[res];
            }

            amiiboVec.clear();
        }

        keyVec.clear();
        if(res < 0) { //Cancelled
            cancelled = true;
        }

        Process::Play();
        return 0;
    }

    u32 AmiiboHook(u32 offset) {
        Task task(SelectAmiibo); // Task needed here, otherwise Process::Pause breaks
        task.Start();
        task.Wait();

        const HookContext &curr = HookContext::GetCurrent();
        static Address func = Address::decodeARMBranch(curr.targetAddress, curr.overwrittenInstr);
        return func.Call<u32>(offset);
    }

    void AmiiboSpoofer(MenuEntry *entry) {
        static Address stateMachineAddr(0x1E9014);
        static Address setAmiiboData(0x1EA8F0); //this seems to get called once when init, so perfect to set data here
        static Hook stateMachineHook, setAmiiboDataHook;

        if (entry->WasJustActivated()) {
            stateMachineHook.InitializeForMitm(stateMachineAddr.addr, (u32)AmiiboStateMachine_Hook);
            stateMachineHook.Enable();

            setAmiiboDataHook.Initialize(setAmiiboData.addr, (u32)AmiiboHook);
            setAmiiboDataHook.SetFlags(USE_LR_TO_RETURN);
            setAmiiboDataHook.Enable();
        }
        else if(!entry->IsActivated()) {
            stateMachineHook.Disable();
            setAmiiboDataHook.Disable();
        }
    }
}