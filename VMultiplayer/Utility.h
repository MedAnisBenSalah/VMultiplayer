/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Utility.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef UTILITY_H
#define UTILITY_H

// TODO: Move that somewhere else
#define PAD(a, b) char a[b]

class CUtility
{

public:
	static void		Unprotect(DWORD64 dwAddress, DWORD dwSize);
	static DWORD64	FindPattern(char *szPattern, char *szMask);
	static void		GetScreenSize(HWND hWindow, int *piWidth, int *piHeight);
	static void		ExitWithError(char *szError, ...);
};

#endif