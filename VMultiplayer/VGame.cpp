/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VGame.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

DWORD CVGame::GetKeyHash(char *szKey)
{
	return CAddress::FUNC_GetHashKey(szKey, 0);
}

void CVGame::ShutdownLoadingScreen()
{
	CAddress::FUNC_ShutdownLoadingScreen(TRUE);
}

void CVGame::FadeScreen(eVSceenFadeType type, int iDuration)
{
	CAddress::FUNC_FadeScreen(iDuration, (BYTE)type);
}

eVGameState CVGame::GetGameState()
{
	// Make sure we initialized
	if (!CAddress::VAR_GameState)
		return VGAME_STATE_UNINITIALIZED;

	return *(eVGameState *)CAddress::VAR_GameState;
}

void CVGame::SetGameState(eVGameState state)
{
	if (CAddress::VAR_GameState)
		*(eVGameState *)CAddress::VAR_GameState = state;
}

void CVGame::Wait(float fTime, VGtaThread *pThread)
{
	// If the thread already running ?
	if (pThread->state == VTHREAD_STATE_RUNNING)
	{
		// Decrease the thread timer
		pThread->dwTimerC -= *(DWORD *)(CCore::GetBaseAddress() + 0x1417DF170);
		// If we finished waiting then set thread to idle
		if (pThread->dwTimerC == 0)
		{
			pThread->state = VTHREAD_STATE_IDLE;
			pThread->dwTimerC = 0;
		}
	}
	else
	{
		// Set the thread time
		pThread->dwTimerC = (DWORD)fTime;
		// Set thread state to running
		pThread->state = VTHREAD_STATE_RUNNING;
	}
}