/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Logger.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#ifndef LOGGER_H
#define LOGGER_H

#ifdef _WIN32
#	include <Windows.h>
#endif

#include <stdio.h>

class CLogger
{

public:
	static bool Open(char *szFile);
	static void Write(char *szBuffer, ...);
	static void Flush();
	static void Close();

private:
	static FILE	*m_pFile;
};

#endif