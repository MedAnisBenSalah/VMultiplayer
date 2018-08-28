/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GameHooks.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/


#include "Main.h"

static bool					bWorldInitialized;
static bool					bPlayerInitialized;

bool c = false;

DWORD GtaThread__Run_Hook(VGtaThread *pThis)
{
	//LOG("proc: %s id: %d", pThis->szName, pThis->iId);
	// Should we initialize
	if (!bWorldInitialized)
	{
		// Initialize after game load
		CCore::OnGameStart();
		// Begin processing the thread
		CCore::GetGame()->BeginProcess(pThis);
		// Spawn local player
		CCore::GetLocalPlayer()->Spawn();
		// Flag the world to be initialized
		bWorldInitialized = true;
		// TODO: Find a fucking FIX for loading models while ingame as it seems to freeze the game
	//	CVStreaming::RequestModel(CVGame::GetKeyHash("player_zero"));
	}
	else
	{
		// Begin processing the thread
		CCore::GetGame()->BeginProcess(pThis);
		// Only process if its our thread
		if (pThis == CCore::GetGame()->GetGtaThread())
		{
			// Should we initialize the player
			if (!bPlayerInitialized)
			{
				// Shutdown loading screen
				CVGame::ShutdownLoadingScreen();
				// Display game graphics
				CCore::GetGraphics()->DoGameLoad();
				// Flag the player to be initialized
				bPlayerInitialized = true; 	
			}
			// F2 is mostly for testing game functions
			if (GetAsyncKeyState(VK_F2) && !c)
			{

			}
			// Process the frame
			CCore::Process();
		}
	}
	// End processing the thread
	CCore::GetGame()->EndProcess(pThis);
	return 1;
}

/*
VGtaThread *GetCurrentGtaThread_Hook()
{
	// Return the current thread
	if (pMultiplayer->GetGame()->GetThreadManager())
		return pMultiplayer->GetGame()->GetThreadManager()->GetThread(0)->GetInterface();
	else
		return NULL;
}
*/
typedef void ( *LoadInto_t)(DWORD dwUnknown, DWORD dwUnknown2);
LoadInto_t LoadInto;
void LoadIntro_Hook(DWORD dwUnknown, DWORD dwUnknown2)
{
	// Load 2D stuff
	LoadInto(dwUnknown, dwUnknown2);
	// Skip to the loading screen
	*(DWORD *)CAddress::VAR_GameState = 6;
}

void CGameHooks::Install()
{
	LOG("CGameHooks::Install()");
	// Reset flags
	bWorldInitialized = false;
	bPlayerInitialized = false;
	// Hook for GtaThread__Run
	CHooks::InstallJmpHook(CAddress::CALLBACK_GtaThread__Run, (DWORD64)GtaThread__Run_Hook); 
	// Hook for LoadIntro, and yeah, by the way find a way to properly skip loading screens
	LoadInto = (LoadInto_t)CHooks::InstallDetoursHook((BYTE *)CCore::GetBaseAddress() + 0x13FD51E54, (BYTE *)LoadIntro_Hook);
	//CHooks::InstallJmpHook(pMultiplayer->GetBaseAddress() + 0x140FC4844, (DWORD64)GtaThread__Run_Hook);0x140167054
	// Hook for GetCurrentGtaThread
//	CHooks::InstallJmpHook(CAddress::CALLBACK_GetCurrentGtaThread, (DWORD64)GetCurrentGtaThread_Hook);

	LOG("CGameHooks::Install Done.");


}
