/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Network.cpp
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace RakNet;

CNetwork::CNetwork(bool bIsServer)
{
	// Set the server flag
	m_bIsServer = bIsServer;
	// Reset pointers
	m_pRakPeer = NULL;
	m_pRFManager = NULL;
}

CNetwork::~CNetwork()
{

}

bool CNetwork::Initialize(int iPort, int iMaxPlayers)
{
	// Get the rakpeer interface
	m_pRakPeer = RakPeerInterface::GetInstance();
	if (!m_pRakPeer)
		return false;

	// Startup the RakPeer
	if (m_pRakPeer->Startup(m_bIsServer ? iMaxPlayers : 1, m_bIsServer ? &SocketDescriptor(iPort, 0) : &SocketDescriptor(), 1) != StartupResult::RAKNET_STARTED)
		return false;

	// Setup RakPeer
	m_pRakPeer->SetOccasionalPing(true);
	// Create the RF manager
	m_pRFManager = new CRFManager();

	return true;
}

bool CNetwork::Connect(char *szHost, int iPort, char *szPassword, int iPasswordLength)
{
	// Try to connect
	if (m_pRakPeer->Connect(szHost, iPort, szPassword, iPasswordLength) != CONNECTION_ATTEMPT_STARTED)
		return false;

	return true;
}

bool CNetwork::Start(int iPort, int iMaxPlayers)
{
	// Set the maximum incoming connections
	m_pRakPeer->SetMaximumIncomingConnections(iMaxPlayers);
	return true;
}

void CNetwork::Send(BitStream *pBitStream, PacketPriority priority, PacketReliability reliability, int iTargetId, bool bBroadcast)
{
	// Send 
	m_pRakPeer->Send(pBitStream, priority, reliability, 0, iTargetId == INVALID_NETWORK_ID ? UNASSIGNED_SYSTEM_ADDRESS :
		m_pRakPeer->GetSystemAddressFromIndex(iTargetId), bBroadcast);
}

CNetMessage *CNetwork::Process()
{
	// Try to receive
	Packet *pPacket = m_pRakPeer->Receive();
	if (!pPacket)
		return NULL;

	// Get the message ID
	unsigned char ucPacketIdentifier = pPacket->data[0];
	switch (ucPacketIdentifier)
	{
		// RF invoking
		case ID_RF_INVOKE:
		{
			// Create the data bitstream
			BitStream bsRead(pPacket->data, pPacket->length, false);
			// Ignore the messageID
			bsRead.IgnoreBytes(sizeof(MessageID));
			// Get the RF ID
			int iRFId = -1;
			if (!bsRead.Read(iRFId))
			{
				// Deallocate the packet
				m_pRakPeer->DeallocatePacket(pPacket);
				return NULL;
			}
			// Create our sender info
			CNetSenderInfo senderInfo(pPacket->systemAddress);
			// Create the RF parameters
			CRFParameters parameters(&bsRead, &senderInfo);
			// Invoke the RF
			m_pRFManager->Invoke(iRFId, &parameters);
			// Deallocate the packet
			m_pRakPeer->DeallocatePacket(pPacket);
			return NULL;
		}
	}
	// Create the return message
	CNetMessage *pMessage = new CNetMessage(pPacket);
	// Deallocate the packet
	m_pRakPeer->DeallocatePacket(pPacket);
	// Return the message
	return pMessage;
}

void CNetwork::DestroyMessage(CNetMessage *pNetMessage)
{
	// Delete the message
	SAFE_DELETE(pNetMessage);
}

void CNetwork::RegisterRemoteFunction(int iRFId, RemoteFunctionInvoke_t pfnCallback)
{
	if (m_pRFManager)
		m_pRFManager->RegisterRemoteFunction(iRFId, pfnCallback);
}

void CNetwork::UnregisterRemoteFunction(int iRFId)
{
	if (m_pRFManager)
		m_pRFManager->UnregisterRemoteFunction(iRFId);
}

void CNetwork::InvokeRF(int iRFId, BitStream *pBitStream, PacketPriority priority, PacketReliability reliability, int iTargetId, bool bBroadcast)
{
	// Create a new bitstream
	BitStream bsSend;
	// Write the packet header
	bsSend.Write((BYTE)ID_RF_INVOKE);
	bsSend.Write(iRFId);
	// Restore the user data
	bsSend.Write(pBitStream);
	// Send
	Send(&bsSend, priority, reliability, iTargetId, bBroadcast);
}
