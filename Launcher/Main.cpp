/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.cpp
-- Project: Client.Launcher
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

// That code belongs to VMultiplayer or LaunchHelper to modify the game when starting
// Reformate the settings path
/*char szSettingsPath[MAX_PATH];
sprintf(szSettingsPath, "%s/"CLIENT_SETTINGS_FILE, szCurrentPath);
// Initialize the configuration file
tinyxml2::XMLDocument xmlSettings;
if (xmlSettings.LoadFile(szSettingsPath) != tinyxml2::XMLError::XML_SUCCESS)
{
MessageBox(NULL, "Couldn't locate \""CLIENT_SETTINGS_FILE"\".\nPlease reinstall V:Multiplayer or visit the website at " WEBSITE " for more details.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
return 0;
}*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCmdLine, int iCmdShow)
{
	// Get the current path 
	char szCurrentPath[MAX_PATH];
	if (!CSharedUtility::GetCurrentPath(szCurrentPath))
	{
		MessageBox(NULL, "An internal error has occured.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	// Read the resgitery key
	char szGamePath[MAX_PATH], szLauncherPath[MAX_PATH];
	if (!CSharedUtility::ReadRegisteryKey("GTAVPath", szGamePath, MAX_PATH))
	{
		// Ask them to specify the path now
		int iResponse = MessageBox(NULL, "Couldn't find GTAV directory path.\nWould you like to choose the path now ?", "V:Multiplayer", MB_YESNO | MB_ICONQUESTION);
		if (iResponse == IDNO)
		{
			MessageBox(NULL, "Couldn't locate \""GAME_EXECUTABLE"\".", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
			return 0;
		}
		// Taken from http://vcfaq.mvps.org/sdk/20.htm
		BROWSEINFO browseInfo = { 0 };
		browseInfo.lpszTitle = "Pick a Directory";
		ITEMIDLIST * pItemIdList = SHBrowseForFolder(&browseInfo);

		if (pItemIdList != NULL)
		{
			// Get the name of the selected folder
			if (!SHGetPathFromIDList(pItemIdList, szGamePath))
			{
				MessageBox(NULL, "Couldn't locate \""GAME_EXECUTABLE"\".", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
				return 0;
			}

			// Free any memory used
			IMalloc * pIMalloc = 0;
			if (SUCCEEDED(SHGetMalloc(&pIMalloc)))
			{
				pIMalloc->Free(pItemIdList);
				pIMalloc->Release();
			}
			// Make the full launcher path
			sprintf(szLauncherPath, "%s\\"GAME_EXECUTABLE, szGamePath);
			// Validate the path
			if (!CSharedUtility::FileExists(szLauncherPath))
			{
				MessageBox(NULL, "Couldn't locate \""GAME_EXECUTABLE"\".", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
				return 0;
			}
			// Write the new path
			if (!CSharedUtility::WriteRegisteryKey("GTAVPath", szGamePath, strlen(szGamePath)))
			{
				// Try to create it now
				if (!CSharedUtility::CreateRegisteryKey("GTAVPath", szGamePath, strlen(szGamePath)))
				{
					MessageBox(NULL, "Couldn't update the GTAV path.\nPlease reinstall V:Multiplayer or visit the website at " WEBSITE " for more details.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
					return 0;
				}
			}
		}
	}
	else
		// Make the full launcher path
		sprintf(szLauncherPath, "%s\\"GAME_EXECUTABLE, szGamePath);

	// Check if the game executable file is valid
	if (!CSharedUtility::FileExists(szLauncherPath))
	{
		MessageBox(NULL, "Couldn't locate \""GAME_EXECUTABLE"\".", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	// Create the full LaunchHelper path
	char szLaunchHelperPath[MAX_PATH];
	sprintf(szLaunchHelperPath, "%s\\"VMULTIPLAYER_LAUNCH_HELPER_LIBRARY, szCurrentPath);
	// Check if the V:Multiplayer librarys are valid
	if (!CSharedUtility::FileExists(szLaunchHelperPath))
	{
		MessageBox(NULL, "Couldn't locate \""VMULTIPLAYER_LAUNCH_HELPER_LIBRARY"\".\nPlease reinstall V:Multiplayer or visit the website at " WEBSITE " for more details.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	// Initialize the STARTUPINFO structure
	STARTUPINFO StartupInfo;
	memset(&StartupInfo, 0, sizeof(StartupInfo));
	// Initialize the PROCESS_INFORMATION structure
	PROCESS_INFORMATION ProcessInfo;
	memset(&ProcessInfo, 0, sizeof(ProcessInfo));
	// Launch the game
	if (!CreateProcess(szLauncherPath, "", NULL, NULL, true, CREATE_SUSPENDED, NULL, NULL, &StartupInfo, &ProcessInfo))
	{
		MessageBox(NULL, "Couldn't start \""GAME_EXECUTABLE"\".", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Try to inject the library
	if (!CSharedUtility::InjectLibrary(ProcessInfo.hProcess, szLaunchHelperPath))
	{
		MessageBox(NULL, "Couldn't inject \"" VMULTIPLAYER_LAUNCH_HELPER_LIBRARY "\" into the game.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Resume the launcher 
	ResumeThread(ProcessInfo.hThread);
	return 1;
}

