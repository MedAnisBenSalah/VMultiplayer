/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Utility.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

void CUtility::Unprotect(DWORD64 dwAddress, DWORD dwSize)
{
	// Unprotect the address
	DWORD dwOldProtection;
	VirtualProtect((LPVOID)dwAddress, dwSize, PAGE_EXECUTE_READWRITE, &dwOldProtection);
}

DWORD64 CUtility::FindPattern(char *szPattern, char *szMask)
{
	// Get the current process information
	MODULEINFO mInfo = { 0 };
	if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &mInfo, sizeof(MODULEINFO)))
		return NULL;

	// Find the base address 
	DWORD64 dwBase = (DWORD64)mInfo.lpBaseOfDll;
	DWORD64 dwSize = (DWORD64)mInfo.SizeOfImage;
	// Get the pattern length
	DWORD64 dwPatternLength = (DWORD64)strlen(szMask);
	// Loop through all the process
	for (DWORD64 i = 0; i < dwSize - dwPatternLength; i++)
	{
		bool bFound = true;
		// Loop through the pattern caracters
		for (DWORD64 j = 0; j < dwPatternLength; j++)
			bFound &= szMask[j] == '?' || szPattern[j] == *(char*)(dwBase + i + j);

		// If found return the current address
		if (bFound)
			return dwBase + i;
	}
	// Return null
	return NULL;
}

void CUtility::GetScreenSize(HWND hWindow, int *piWidth, int *piHeight)
{
	// Get window rect
	RECT rectWindow;
	GetWindowRect(hWindow, &rectWindow);
	// Set the values
	*piWidth = rectWindow.right;
	*piHeight = rectWindow.bottom;
}

void CUtility::ExitWithError(char *szError, ...)
{
	// Start the arguments list
	va_list vArgs;
	va_start(vArgs, szError);
	// Create the error string
	char szErrorBuffer[256];
	vsprintf(szErrorBuffer, szError, vArgs);
	// Display the error
	MessageBox(NULL, szErrorBuffer, NAME" Error", MB_OK | MB_ICONERROR);
	// End the arguments list
	va_end(vArgs);
	// Quit
	ExitProcess(0);
}