/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.cpp
-- Project: Client.LaunchHelper
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

// Client path
char szClientPath[MAX_PATH];

// Type definition for CreateProcess function
typedef HRESULT(WINAPI* CreateProcess_t)(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);

// Pointer to the function
CreateProcess_t pfn_CreateProcess = NULL;

// Hook for the CreateProcess function
BOOL WINAPI CreateProcess_Hook(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
	// Suspend the process creation
	dwCreationFlags |= CREATE_SUSPENDED;
	// Set the game full path
	char szFullPath[MAX_PATH];
	CSharedUtility::GetCurrentPath(szFullPath);
	sprintf(szFullPath, "%s\\%s", szFullPath, lpApplicationName);
	// Create the game process
	wchar_t lpFullPath[MAX_PATH];
	swprintf(lpFullPath, L"%s", szFullPath);
	if (!pfn_CreateProcess(lpFullPath, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation))
	{
		MessageBox(NULL, "Couldn't launch the game", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Try to inject the library
	if (!CSharedUtility::InjectLibrary(lpProcessInformation->hProcess, szClientPath))
	{
		MessageBox(NULL, "Couldn't inject library \"" VMULTIPLAYER_LIBRARY "\".", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Resume the game 
	ResumeThread(lpProcessInformation->hThread);
	// Return succeeded
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Disable thread calls
		DisableThreadLibraryCalls(hModule);
		// Get the current path 
		char szCurrentPath[MAX_PATH];
		if (!CSharedUtility::GetCurrentLibraryPath(VMULTIPLAYER_LAUNCH_HELPER_LIBRARY, szCurrentPath))
		{
			MessageBox(NULL, "An internal error has occured.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
			return 0;
		}
		// Create the full client path
		sprintf(szClientPath, "%s\\"VMULTIPLAYER_LIBRARY, szCurrentPath);
		// Check if the V:Multiplayer librarys are valid
		if (!CSharedUtility::FileExists(szClientPath))
		{
			MessageBox(NULL, "Couldn't locate \""VMULTIPLAYER_LIBRARY"\".\nPlease reinstall V:Multiplayer or visit the website at " WEBSITE " for more details.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		// Initialize MinHook
		if (MH_Initialize() != MH_OK)
		{
			MessageBox(NULL, "Couldn't initialize hooking library.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		// Install CreateProcess hook
		if (MH_CreateHookApi(L"Kernel32.dll", "CreateProcessA", &CreateProcess_Hook, reinterpret_cast<LPVOID *>(&pfn_CreateProcess)) != MH_OK)
		{
			MessageBox(NULL, "Couldn't install hooks.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		// Enable the hook
		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		{
			MessageBox(NULL, "Couldn't enable hooks.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		return 1;
	}

	else if (dwReason == DLL_PROCESS_DETACH)
	{
		// Disable the hook
		if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
		{
			return 1;
		}
		// Uninitialize MinHook.
		if (MH_Uninitialize() != MH_OK)
		{
			return 1;
		}
		return 1;
	}
}

