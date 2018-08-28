/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Network.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#ifndef NETWORK_H
#define NETWORK_H

#define INVALID_NETWORK_ID -1

class CNetwork
{
public:
	CNetwork(bool bIsServer);
	~CNetwork();

	virtual bool Initialize(int iPort, int iMaxPlayers);
	virtual void Send(RakNet::BitStream *pBitStream, PacketPriority priority, PacketReliability reliability, int iTargetId, bool bBroadcast);
	virtual CNetMessage *Process();
	virtual void DestroyMessage(CNetMessage *pNetMessage);
	virtual void RegisterRemoteFunction(int iRFId, RemoteFunctionInvoke_t pfnCallback);
	virtual void UnregisterRemoteFunction(int iRFId);
	virtual void InvokeRF(int iRFId, RakNet::BitStream *pBitStream, PacketPriority priority, PacketReliability reliability, int iTargetId, bool bBroadcast);

	// Client functions
	virtual bool Connect(char *szHost, int iPort, char *szPassword, int iPasswordLength);

	// Server functions
	virtual bool Start(int iPort, int iMaxPlayers);


private:
	bool							m_bIsServer;
	RakNet::RakPeerInterface		*m_pRakPeer;
	CRFManager						*m_pRFManager;
};

#endif