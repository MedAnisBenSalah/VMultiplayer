/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VThread.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CVThread::CVThread(VGtaThread *pThread)
{
	// Set the thread interface
	SetInterface(pThread);
}

CVThread::~CVThread()
{

}

int CVThread::GetId()
{
	// Validate the interface
	if (!GetInterface())
		return 0;

	return GetInterface()->iId;
}

void CVThread::SetId(int iId)
{
	// Validate the interface
	if (GetInterface())
		GetInterface()->iId = iId;
}

eVThreadState CVThread::GetState()
{
	// Validate the interface
	if (!GetInterface())
		return VTHREAD_STATE_IDLE;

	return GetInterface()->state;
}

void CVThread::SetState(eVThreadState state)
{
	// Validate the interface
	if (GetInterface())
		GetInterface()->state = state;
}

void CVThread::GetName(char *szName)
{
	// Validate the interface
	if (GetInterface())
		strcpy(szName, GetInterface()->szName);
	else
		strcpy(szName, "");
}

void CVThread::SetName(char *szName)
{
	// Validate the interface
	if (GetInterface())
		strcpy(GetInterface()->szName, szName);
}