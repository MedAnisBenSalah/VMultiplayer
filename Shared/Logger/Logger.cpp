/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Logger.cpp
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#include "Logger.h"

FILE	*CLogger::m_pFile = NULL;

bool CLogger::Open(char *szFile)
{
	// Try to read the file
	m_pFile = fopen(szFile, "wb");
	if (!m_pFile)
		return false;

	return true;
}

void CLogger::Write(char *szBuffer, ...)
{
	// Validate the file pointer
	if (!m_pFile)
		return;

	// Start the arguments list
	va_list vArgs;
	va_start(vArgs, szBuffer);
#ifdef _WIN32
	// Get the system time
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	// Write time to the log file
	fprintf(m_pFile, "[%d:%d:%d] ", systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
#else
	// Do some linux time retrieving code in here
#endif
	// Write the text to the log file
	vfprintf(m_pFile, szBuffer, vArgs);
	// New lines
	fprintf(m_pFile, "\r\n");
	// End the arguments list
	va_end(vArgs);
}

void CLogger::Flush()
{
	// Validate the file pointer
	if (!m_pFile)
		return;

	// Flush the file
	fflush(m_pFile);
}

void CLogger::Close()
{
	// Validate the file pointer
	if (!m_pFile)
		return;

	// Close the file
	fclose(m_pFile);
	m_pFile = NULL;
}
