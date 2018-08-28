/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VThreadManger.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VTHREADAMANAGER_H
#define VTHREADAMANAGER_H

#define MAX_VTHREADS 512

#pragma pack(push, 1)
class VThreadManager
{
public:
	VGtaThread				*pThread[MAX_VTHREADS]; // Unknown limit for now
};
#pragma pack(pop)

class CVThreadManager : public CVObjectBase<VThreadManager>
{
public:
	CVThreadManager(VThreadManager *pThreadManager);
	~CVThreadManager();

	CVThread	*GetThread(int iThreadId);
	void		SetThread(int iThreadId, VGtaThread *pGtaThread);

	VGtaThread *CreateThread(char *szName);
	void Update(WORD wThreadCount);
	void Shutdown();

private:
	CVThread		*m_pThread[MAX_VTHREADS];
};

#endif