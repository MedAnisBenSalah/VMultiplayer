/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Thread.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#ifndef THREAD_H
#define THREAD_H

#ifdef _WIN32
#	include <Windows.h>
#endif

typedef void (*ThreadCallback_t)(void *pThread);

class CThread
{
	public:
		CThread(ThreadCallback_t pfn_ThreadCallback);
		~CThread();

		bool Start();
		void Kill();
		bool IsStarted() { return m_bStarted; };
		void SetStarted(bool bState) { m_bStarted = bState; };
		void Run(CThread *pThread) { m_pfnThreadCallback((void *)pThread); };
#ifdef _WIN32
		static void StaticThreadRun(void *pThread);
#else
		static void *StaticThreadRun(void *pThread);
#endif

	private:
		bool				m_bStarted;
		ThreadCallback_t	m_pfnThreadCallback;
#ifdef _WIN32
		HANDLE				m_hThread;
#else
		pthread_t			m_Thread;
#endif

};

#endif
