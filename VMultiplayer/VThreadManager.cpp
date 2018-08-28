/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VThreadManager.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CVThreadManager::CVThreadManager(VThreadManager *pThreadManager)
{
	// Set the thread manager interface
	SetInterface(pThreadManager);
	// Reset thread pointers
	for (WORD i = 0; i < MAX_VTHREADS; i++)
		m_pThread[i] = NULL;
}

CVThreadManager::~CVThreadManager()
{
	// Delete all thread instances
	Shutdown();
}

CVThread *CVThreadManager::GetThread(int iThreadId)
{
	// Validate the interface
	if (!GetInterface())
		return NULL;

	// Create a new thread instance
	return m_pThread[iThreadId];
}

void CVThreadManager::SetThread(int iThreadId, VGtaThread *pGtaThread)
{
	// Set the thread pointer
	if (GetInterface())
		GetInterface()->pThread[iThreadId] = pGtaThread;
}

typedef void(*Create_t)(DWORD64 dwThis, VGtaThread *pThread);
Create_t FUNC_CGameScriptHandlerMgr__CreateThreadScriptHandler;

VGtaThread *CVThreadManager::CreateThread(char *szName)
{
	// TODO: Find why creating a new thread crashes
	// Allocate for a new thread
	/*VGtaThread *pThread = CVGame::GtaAllocate<VGtaThread>(sizeof(VGtaThread));
	if (!pThread)
		return NULL;

	// Call the thread constructor
	CAddress::FUNC_GtaThread__Constructor(pThread);
	// Increase the threads count
	*(WORD *)CAddress::VAR_ThreadsCount = *(WORD *)CAddress::VAR_ThreadsCount + 1;
	// Add the thread to the thread manager
	SetThread(*(WORD *)CAddress::VAR_ThreadsCount, pThread);*/

	// Find a free thread slot
	int iSlot = -1;
	for (int i = 5; i < *(WORD *)CAddress::VAR_ThreadsCount; i++)
	{
		if (!GetInterface()->pThread[i]->iId)
		{
			iSlot = i;
			break;
		}
	}
	// Did we get a valid slot
	if (iSlot == -1)
		return NULL;

	// Increase the thread id and count
	*(DWORD *)(CCore::GetBaseAddress() + 0x14255408C) = *(DWORD *)(CCore::GetBaseAddress() + 0x14255408C) + 1;
	*(DWORD *)(CCore::GetBaseAddress() + 0x142553284) = *(DWORD *)(CCore::GetBaseAddress() + 0x142553284) + 1;
	// Get the thread
	VGtaThread *pThread = GetThread(iSlot)->GetInterface();
	// Set its parameters
	pThread->iId = iSlot + 1;
	pThread->state = VTHREAD_STATE_RUNNING;
	pThread->dwSet1 = 1;
	pThread->dwUnknown1 = -1;
	pThread->dwUnknown2 = -1;
	strcpy(pThread->szName, szName);
	// Create the script handler for this thread
	FUNC_CGameScriptHandlerMgr__CreateThreadScriptHandler = (Create_t)(CCore::GetBaseAddress() + 0x140FD2774);
	FUNC_CGameScriptHandlerMgr__CreateThreadScriptHandler(CCore::GetBaseAddress() + 0x141E44A80, pThread);
	// Update our thread manager
	//Update(*(WORD *)CAddress::VAR_ThreadsCount);
	return pThread;
}

void CVThreadManager::Update(WORD wThreadCount)
{
	// Validate the interface
	if (!GetInterface())
		return;

	// Loop through all the threads
	for (WORD i = 0; i < wThreadCount; i++)
	{
		// Validate the thread
		if (GetInterface()->pThread[i])
		{
			// If the thread is valid then change its interface
			if (m_pThread[i])
			{
				if(m_pThread[i]->GetInterface() != GetInterface()->pThread[i])
					m_pThread[i]->SetInterface(GetInterface()->pThread[i]);
			}
			else
				// Create an instance for that thread
				m_pThread[i] = new CVThread(GetInterface()->pThread[i]);
		}
	}
}

void CVThreadManager::Shutdown()
{
	// Delete all thread pointers
	for (WORD i = 0; i < MAX_VTHREADS; i++)
	{
		if (m_pThread[i])
			SAFE_DELETE(m_pThread[i]);
	}
}