/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.cpp
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CServer		*pServer = NULL;
bool		bIsRunning = false;

// TODO: Move these to a CUtility class
void LogPrintf(char *szBuffer, ...)
{
	// Start the arguments list
	va_list vArguments;
	va_start(vArguments, szBuffer);
	// Log
	//LOG(szBuffer, vArguments);
	CLogger::Write(szBuffer, vArguments);
	CLogger::Flush();
	// Print to the screen
	vprintf(szBuffer, vArguments);
	printf("\n");
	// End the arguments list
	va_end(vArguments);
}

void FatalError(char *szError, ...)
{
	// Start the arguments list
	va_list vArguments;
	va_start(vArguments, szError);
	// Log the error
	LogPrintf(szError, vArguments);
	// End the arguments list
	va_end(vArguments);
	// Exit
	system("PAUSE");
	exit(0);
}

int main()
{
	// Open the log file
	if (!CLogger::Open(LOG_FILE))
		FatalError("Failed to open \"" LOG_FILE "\".");

	// Starting messages
	LogPrintf(NAME " Dedicated Server:");
	LogPrintf("--------------------------------");
	LogPrintf("Version: " VERSION);
	LogPrintf("Build: " __DATE__);
	LogPrintf("Author: V:Multiplayer Team");
	LogPrintf("--------------------------------");
	LogPrintf("");
	// Create the server instance
	LogPrintf("Starting server (Port: %d) ...", 5555);
	pServer = new CServer();
	// Start the server
	if (!pServer || !pServer->LoadComponents() || !pServer->Initialize(5555, 32) || !pServer->Start(5555, 32))
		FatalError("Failed to start the server.");

	LogPrintf("Server successfully started.\n");
	// Main loop
	bIsRunning = true;
	int i = 1;
	DWORD tick = GetTickCount();
	while (bIsRunning)
	{
		// Process the server
		pServer->Process();
		if (GetAsyncKeyState(VK_F3) && (GetTickCount() - tick) > 3000)
		{
			if (pServer->GetPlayerManager()->IsValid(i))
			{
				pServer->GetPlayerManager()->RemovePlayer(i, LEFT_REASON_TIMEOUT);
				LogPrintf("Removed %d", i);
			}
			else
			{
				pServer->GetPlayerManager()->AddPlayer(i, "test_");
				pServer->GetPlayerManager()->GetAt(i)->AddForWorld();
				pServer->GetPlayerManager()->GetAt(i)->SpawnForWorld();
				LogPrintf("Added %d", i);
			}
			tick = GetTickCount();
		}
		Sleep(5);
	}
	return 1;
}