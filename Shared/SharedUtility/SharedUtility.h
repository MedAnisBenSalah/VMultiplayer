/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: SharedUtility.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#ifndef SHAREDUTILITY_H
#define SHAREDUTILITY_H

#ifdef _WIN32
#	include <Windows.h>
#endif

#include <stdio.h>

class CSharedUtility
{

public:
	static bool FileExists(char *szFile);
	static bool InjectLibrary(HANDLE hProcess, char *szLibrary);
	static bool GetCurrentPath(char *szOutput);
	static bool ReadRegisteryKey(char *szKey, char *szOutput, DWORD dwOutputSize);
	static bool GetCurrentLibraryPath(char *szLibrary, char *szOutput);
	static bool WriteRegisteryKey(char *szKey, char *szBuffer, DWORD dwBufferSize);
	static bool CreateRegisteryKey(char *szKey, char *szBuffer, DWORD dwBufferSize);
	static void FixPath(char *szPath);
};

#endif