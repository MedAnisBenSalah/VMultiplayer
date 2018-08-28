/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Server.cpp
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

typedef CNetwork *(*VMultiplayer_CreateNetwork_t)(bool bIsServer);
VMultiplayer_CreateNetwork_t		pfnVMultiplayer_CreateNetwork = NULL;

CServer::CServer()
{
	// Reset pointers
	m_pNetwork = NULL;
	m_pNetworkComponent = NULL;
	m_pPlayerManager = NULL;
	// Reset flags
	m_bInitialized = false;
}

CServer::~CServer()
{

}

bool CServer::LoadComponents()
{
	// Load the network component
	m_pNetworkComponent = new CComponent("Network_x32");
	if (!m_pNetworkComponent || !m_pNetworkComponent->Load())
	{
		LogPrintf("Failed to load the network component.");
		return false;
	}
	return true;
}

bool CServer::Initialize(int iPort, int iMaxPlayers)
{
	// Make sure we are not already initialized
	if (m_bInitialized)
		return true;

	// Get the initializing funtion address
	pfnVMultiplayer_CreateNetwork = m_pNetworkComponent->GetInitializeAddress<VMultiplayer_CreateNetwork_t>();
	if (!pfnVMultiplayer_CreateNetwork)
		return false;

	// Create the network instance
	m_pNetwork = pfnVMultiplayer_CreateNetwork(true);
	// Try to initialize the network
	if (!m_pNetwork->Initialize(iPort, iMaxPlayers))
		return false;

	// Create managers
	m_pPlayerManager = new CPlayerManager();
	// Flag as initialized
	m_bInitialized = true;
	return true;
}

bool CServer::Start(int iPort, int iMaxPlayers)
{
	// Try to connect
	if (!m_pNetwork->Start(iPort, iMaxPlayers))
		return false;

	// Register all RFs
	CMainRFS::RegisterRFS(m_pNetwork);
	CPlayerRFS::RegisterRFS(m_pNetwork);
	return true;
}

void CServer::Process()
{
	// Update player manager
	if (m_pPlayerManager)
		m_pPlayerManager->Process();

	// Update the network
	CNetMessage *pMessage = m_pNetwork->Process();
	if (!pMessage)
		return;

	// Process each message
	switch (pMessage->GetMessageID())
	{
	// New connection request
	case ID_NEW_INCOMING_CONNECTION:
		LogPrintf("New connection request from %s ...", pMessage->GetSenderInfo()->GetIP());
		break;

	// On lost connection
	case ID_CONNECTION_LOST:
	{
		// Get player id
		int iPlayerId = pMessage->GetSenderInfo()->GetID();
		if (!m_pPlayerManager->IsValid(iPlayerId))
			break;

		// Delete the player
		m_pPlayerManager->RemovePlayer(iPlayerId, LEFT_REASON_TIMEOUT);
		break;
	}
	// On player disconnected
	case ID_DISCONNECTION_NOTIFICATION:
	{
		// Get player id
		int iPlayerId = pMessage->GetSenderInfo()->GetID();
		if (!m_pPlayerManager->IsValid(iPlayerId))
			break;

		// Delete the player
		m_pPlayerManager->RemovePlayer(iPlayerId, LEFT_REASON_DISCONNECTED);
		break;
	}
	// Player on foot sync
	case ID_SYNC_PLAYER:
	{
		// Get player id
		int iPlayerId = pMessage->GetSenderInfo()->GetID();
		if (!m_pPlayerManager->IsValid(iPlayerId))
			break;
		
		// Store player sync data
		m_pPlayerManager->GetAt(iPlayerId)->StoreOnFootSyncData(pMessage->GetBitStream());
		break;
	}
	}
}

void CServer::SendEntities(int iPlayerId)
{
	// Validate the player
	if (!m_pPlayerManager->IsValid(iPlayerId))
		return;

	// NOTE: we create vehicles before players so we won't have problems putting players inside them
	// Loop through all the active players
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		// Is the player active ?
		if (m_pPlayerManager->IsValid(i) && m_pPlayerManager->GetAt(i) && i != iPlayerId)
			m_pPlayerManager->GetAt(i)->AddForPlayer(iPlayerId);
	}
}