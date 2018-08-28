/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.cpp
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

#ifdef _WIN64
EXPORT CNetwork *VMultiplayer_CreateNetwork_x64(bool bIsServer)
#else
EXPORT CNetwork *VMultiplayer_CreateNetwork_x32(bool bIsServer)
#endif
{
	return new CNetwork(bIsServer);
}
#ifdef _WIN64
EXPORT void VMultiplayer_DestroyNetwork_x64(CNetwork *pNetwork)
#else
EXPORT void VMultiplayer_DestroyNetwork_x32(CNetwork *pNetwork)
#endif
{
	SAFE_DELETE(pNetwork);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Disable thread calls
		DisableThreadLibraryCalls(hModule);
		// Get the log full path
		char szLogPath[MAX_PATH];
#ifdef NETWORK_X32
		CSharedUtility::GetCurrentLibraryPath(VMULTIPLAYER_NETWORK_LIBRARY_x32, szLogPath);
#else
		CSharedUtility::GetCurrentLibraryPath(VMULTIPLAYER_NETWORK_LIBRARY_x64, szLogPath);
#endif
		strcat(szLogPath, "\\"LOG_FILE);
		// Open log file
		if (!CLogger::Open(szLogPath))
		{
			MessageBox(NULL, "Couldn't open network log file.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		LOG("Network Library loaded.");

		return TRUE;
	}

	if (dwReason == DLL_PROCESS_DETACH)
	{
		// Close log file
		CLogger::Close();
		return 1;
	}
}

