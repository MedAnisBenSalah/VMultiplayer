/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: RemoteFunction.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#ifndef REMOTEFUNCTION_H
#define REMOTEFUNCTION_H

typedef void(*RemoteFunctionInvoke_t)(CRFParameters *pRFParameters);

class CRemoteFunction
{
public:
	CRemoteFunction(int iRFId, RemoteFunctionInvoke_t pfnCallback);
	~CRemoteFunction();

	int	GetID() { return m_iLocalId; };

	void Invoke(CRFParameters *pRFParameters);


private:
	int								m_iLocalId;
	RemoteFunctionInvoke_t			m_pfnCallback;
};

#endif