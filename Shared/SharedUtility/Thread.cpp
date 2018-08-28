/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Thread.cpp
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#include "Thread.h"

CThread::CThread(ThreadCallback_t pfn_ThreadCallback)
{
	// Reset thread handle
#ifdef _WIN32
	m_hThread = NULL;
#else
	m_Thread = 0;
#endif
	// Reset flags
	m_bStarted = false;
	// Save thread callback
	m_pfnThreadCallback = pfn_ThreadCallback;
}

CThread::~CThread()
{
	// Stop the thread if running
	Kill();
}

bool CThread::Start()
{
	// Exit if we are already running
	if(m_bStarted)
		return false;

	// Start the thread
#ifdef _WIN32
	m_hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)StaticThreadRun, (LPVOID)this, NULL, NULL); 
#else
	pthread_create(&m_Thread, NULL, StaticThreadRun, (void *)this);
#endif

	return true;
}

void CThread::Kill()
{
	// If the thread is not started then dont bother go any further
	if(!m_bStarted)
		return;

#ifdef _WIN32
	// Terminate the thread
	TerminateThread(m_hThread, 0);
	// Delete the thread
	CloseHandle(m_hThread);
#else
	// Delete the thread
	pthread_cancel(m_Thread);
#endif

	// Mark not started
	m_bStarted = false;
	// Reset thread handle
#ifdef _WIN32
	m_hThread = NULL;
#else
	m_Thread = 0;
#endif
}

#ifdef _WIN32
void CThread::StaticThreadRun(void *pThread)
#else
void *CThread::StaticThreadRun(void *pThread)
#endif
{
	// Get thread pointer
	CThread *pThisThread = (CThread *)pThread;
	// Mark started
	pThisThread->SetStarted(true);
	// Call the function callback
	pThisThread->Run(pThisThread);
	// Return
#ifndef _WIN32
	return (void *)1;
#endif
}





