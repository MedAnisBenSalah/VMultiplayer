/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: RFManager.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#ifndef RFMANAGER_H
#define RFMANAGER_H

#include <vector>

class CRFManager
{
public:
	CRFManager();
	~CRFManager();

	void RegisterRemoteFunction(int iRFId, RemoteFunctionInvoke_t pfnCallback);
	void UnregisterRemoteFunction(int iRFId);

	int Find(int iRFId, CRemoteFunction **ppReturnedRF);

	void Invoke(int iRFId, CRFParameters *pRFParameters);


private:
	std::vector<CRemoteFunction *>			m_vectorRF;
};

#endif