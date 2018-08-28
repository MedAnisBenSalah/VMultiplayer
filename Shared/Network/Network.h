/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Network.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#ifndef NETWORK_H
#define NETWORK_H

#include "PacketPriority.h"

#define INVALID_NETWORK_ID -1

class CNetwork
{
public:
	virtual bool Initialize(int iPort, int iMaxPlayers) = 0;
	virtual void Send(BitStream *pBitStream, PacketPriority priority, PacketReliability reliability, int iTargetId, bool bBroadcast) = 0;
	virtual CNetMessage *Process() = 0;
	virtual void DestroyMessage(CNetMessage *pNetMessage) = 0;
	virtual void RegisterRemoteFunction(int iRFId, RemoteFunctionInvoke_t pfnCallback) = 0;
	virtual void UnregisterRemoteFunction(int iRFId) = 0;
	virtual void InvokeRF(int iRFId, BitStream *pBitStream, PacketPriority priority, PacketReliability reliability, int iTargetId, bool bBroadcast) = 0;


	// Client functions
	virtual bool Connect(char *szHost, int iPort, char *szPassword, int iPasswordLength) = 0;

	// Server functions
	virtual bool Start(int iPort, int iMaxPlayers) = 0;
};

#endif