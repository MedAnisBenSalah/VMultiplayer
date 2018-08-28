/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: ExceptionHandler.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/


#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#ifdef _WIN32
#	include <Windows.h>
#	include <psapi.h>
#else
#	include <signal.h>
#endif
#include <stdio.h>

class CExceptionHandler
{
public:
	static void Install(char *szTargetPath);
	static void GetExceptionName(DWORD dwCode, char *szOutput);

	// Exception handler callback
#ifdef _WIN32
	static long WINAPI ExceptionHandlerCallback(_EXCEPTION_POINTERS *pExceptionInfo);
#else 
	static void ExceptionHandlerCallback(int param);
#endif 

private:
	static char		szPath[MAX_PATH];
};

#endif