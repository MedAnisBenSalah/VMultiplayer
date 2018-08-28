/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: SharedUtility.cpp
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#include "SharedUtility.h"

bool CSharedUtility::FileExists(char *szFile)
{
	// Try to read the file
	FILE *pFile = fopen(szFile, "rb");
	if (!pFile)
		return false;

	// Close the file and return
	fclose(pFile);
	return true;
}

bool CSharedUtility::InjectLibrary(HANDLE hProcess, char *szLibrary)
{
#ifdef _WIN32
	// Validate the process handle
	if (!hProcess)
		return false;

	// Get the "LoadLibrary" function address
	FARPROC fpLoadLibrary = NULL;
	if (!(fpLoadLibrary = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA")))
		return false;

	// Allocate for the function call
	LPVOID lpvLoad = NULL;
	if (!(lpvLoad = (LPVOID)VirtualAllocEx(hProcess, NULL, strlen(szLibrary) + 1, MEM_COMMIT, PAGE_READWRITE)))
		return false;

	// Write to the process
	if(!WriteProcessMemory(hProcess, lpvLoad, szLibrary, strlen(szLibrary) + 1, NULL))
		return false;

	// Create remote thread into the process
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)fpLoadLibrary, lpvLoad, NULL, NULL);
	if (!hThread)
		return false;

	// Wait for the remote thread
	WaitForSingleObject(hThread, INFINITE);
	// Close the thread handle
	CloseHandle(hThread);
	// Free the allocated memory
	VirtualFreeEx(hProcess, lpvLoad, strlen(szLibrary) + 1, MEM_RELEASE);
	// Return true
	return true;
#else
	return false;
#endif
}

bool CSharedUtility::GetCurrentPath(char *szOutput)
{
#ifdef _WIN32
	GetModuleFileName(GetModuleHandle(NULL), szOutput, MAX_PATH);
#else
	// Taken from IVMP
	readlink("/proc/self/exe", szOutput, MAX_PATH);
#endif
	char *szOutputPath = szOutput;
	// Validate the string
	if (szOutputPath && strlen(szOutputPath) != 0)
	{
		// Get to the end of string
		while (*szOutputPath != 0)
			szOutputPath++;

		// One substract to avoid EOS
		szOutputPath--;
		// Find the last backslash
		while (*szOutputPath != '\\' && *szOutputPath != '/')
		{
			// Check the end of string
			if (*szOutputPath == 0)
				return false;

			szOutputPath--;
		}
		// Check the end of string
		if (*szOutputPath == 0)
			return false;

		// Copy the final result
		szOutput[strlen(szOutput) - strlen(szOutputPath)] = 0;
		return true;
	}
	return false;
}

bool CSharedUtility::GetCurrentLibraryPath(char *szLibrary, char *szOutput)
{
#ifdef _WIN32
	GetModuleFileName(GetModuleHandle(szLibrary), szOutput, MAX_PATH);
	char *szOutputPath = szOutput;
	// Validate the string
	if (szOutputPath && strlen(szOutputPath) != 0)
	{
		// Get to the end of string
		while (*szOutputPath != 0)
			szOutputPath++;

		// One substract to avoid EOS
		szOutputPath--;
		// Find the last backslash
		while (*szOutputPath != '\\' && *szOutputPath != '/')
		{
			// Check the end of string
			if (*szOutputPath == 0)
				return false;

			szOutputPath--;
		}
		// Check the end of string
		if (*szOutputPath == 0)
			return false;

		// Copy the final result
		szOutput[strlen(szOutput) - strlen(szOutputPath)] = 0;
		return true;
	}
#endif
	return false;
}

bool CSharedUtility::ReadRegisteryKey(char *szKey, char *szOutput, DWORD dwOutputSize)
{
#ifdef _WIN32
	// Open the registry key
	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\VMultiplayer", 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return false;

	// Get the key value
	if (RegQueryValueEx(hKey, szKey, 0, NULL, (LPBYTE)szOutput, &dwOutputSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}
	// Close the registery key
	RegCloseKey(hKey);
	return true;
#else
	// There is not registery keys in linux
	return false;
#endif
}

bool CSharedUtility::WriteRegisteryKey(char *szKey, char *szBuffer, DWORD dwBufferSize)
{
#ifdef _WIN32
	// Open the registry key
	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\VMultiplayer", 0, KEY_WRITE, &hKey) != ERROR_SUCCESS)
		return false;

	// Write the key value
	if (RegSetValueEx(hKey, szKey, 0, REG_SZ, (const BYTE *)szBuffer, dwBufferSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}
	// Close the registery key
	RegCloseKey(hKey);
	return true;
#else
	// There is not registery keys in linux
	return false;
#endif
}

bool CSharedUtility::CreateRegisteryKey(char *szKey, char *szBuffer, DWORD dwBufferSize)
{
#ifdef _WIN32
	// Create the registry key
	HKEY hKey;
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\VMultiplayer", 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS)
		return false;

	// Write the key value
	if (RegSetValueEx(hKey, szKey, 0, REG_SZ, (const BYTE *)szBuffer, dwBufferSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}
	// Close the registery key
	RegCloseKey(hKey);
	return true;
#else
	// There is not registery keys in linux
	return false;
#endif
}

void CSharedUtility::FixPath(char *szPath)
{
	// Copy the path output
	while (*szPath != 0)
	{
		// Replace every backslah with a slash
		while (*szPath != '\\')
			// Increase buffer
			szPath++;

		// Fix the caracter
		*szPath = '/';
		// Increase buffer
		szPath++;
	}
}