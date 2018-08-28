/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

/* CPed: 
0x1078: pPlayerInfo
0xEC0: pIKManager


CPlayerInfo:
0x120: pPed

CNetwork: (0x1420FAD38)
+ 0x7F78: iState (0 = InactiveSession / 5 = InSession / 8 = SessionStarted)

*/

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	// On load
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Disable thread calls
		DisableThreadLibraryCalls(hModule);
		// Open log file
		if (!CLogger::Open(LOG_FILE))
		{
			MessageBox(NULL, "Couldn't open log file.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		// Find the current path
		char szFullPath[MAX_PATH];
		CSharedUtility::GetCurrentPath(szFullPath);
		// Set the current directory to use the default GTA5 directory
		SetCurrentDirectory(szFullPath);
		// Load components
		CCore::LoadComponents();
		// Initialize the core
		CCore::Initialize();
		// Load settings
		CCore::LoadSettings();

		LOG("V:Multiplayer loaded.");
	}
	// On unload
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		// Close log file
		CLogger::Close();
		// Quit
		//CCore::Quit();
	}
	return TRUE;
}
