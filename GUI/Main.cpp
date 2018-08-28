/* =========================================================
        V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.cpp
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

EXPORT CGUI *VMultiplayer_CreateGUI(void *pDevice)
{
	return new CGUI(reinterpret_cast<ID3D11Device *>(pDevice));
}

EXPORT void VMultiplayer_DestroyGUI(CGUI *pGUI)
{
	SAFE_DELETE(pGUI);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Disable thread calls
		DisableThreadLibraryCalls(hModule);
		// Get the log full path
		char szLogPath[MAX_PATH];
		CSharedUtility::GetCurrentLibraryPath(VMULTIPLAYER_GUI_LIBRARY, szLogPath);
		strcat(szLogPath, "\\"LOG_FILE);
		// Open log file
		if (!CLogger::Open(szLogPath))
		{
			MessageBox(NULL, "Couldn't open GUI log file.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		LOG("GUI Library loaded.");
	
		return TRUE;
	}

	if (dwReason == DLL_PROCESS_DETACH)
	{
		// Close log file
		CLogger::Close();
		return 1;
	}
}

