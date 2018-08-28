/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: NetworkPlayer.cpp
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

extern CServer	*pServer;

CNetworkPlayer::CNetworkPlayer(int iPlayerId, char *szPlayerName)
{
	// Save data
	m_iPlayerId = iPlayerId;
	strcpy(m_szPlayerName, szPlayerName);
	// Reset flags
	m_bSpawned = false;
	m_bHasSync = false;
	// Set state
	m_state = PLAYER_STATE_CONNECTED;
}

CNetworkPlayer::~CNetworkPlayer()
{

}

void CNetworkPlayer::AddForWorld()
{
	BitStream bsSend;
	// Write player ID
	bsSend.Write(m_iPlayerId);
	// Write data
	bsSend.Write(m_szPlayerName);
	// Write spawned flag
	bsSend.Write(m_bSpawned);
	// Send the player join RF
	pServer->GetNetwork()->InvokeRF(eRFIdentifier::ID_RF_PLAYER_JOIN, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, m_iPlayerId, true);
}

void CNetworkPlayer::AddForPlayer(int iPlayerId)
{
	BitStream bsSend;
	// Write player ID
	bsSend.Write(m_iPlayerId);
	// Write data
	bsSend.Write(m_szPlayerName);
	// Write spawned flag
	bsSend.Write(m_bSpawned);
	// Send the player join RF
	pServer->GetNetwork()->InvokeRF(eRFIdentifier::ID_RF_PLAYER_JOIN, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, iPlayerId, false);
}

void CNetworkPlayer::SpawnForWorld()
{
	BitStream bsSend;
	// Write player ID
	bsSend.Write(m_iPlayerId);
	// TODO: Write spawn data (eg: position, model, rotation ...)
	// Send the player join RF
	pServer->GetNetwork()->InvokeRF(eRFIdentifier::ID_RF_PLAYER_SPAWN, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, INVALID_NETWORK_ID, true);
	// Set state
	m_state = PLAYER_STATE_ONFOOT;
}

void CNetworkPlayer::Process()
{
	// Does the player have sync data ?
	if (m_bHasSync)
	{

	}
}

void CNetworkPlayer::StoreOnFootSyncData(BitStream *pBitStream)
{
	// Validate the player state
	if (m_state != PLAYER_STATE_ONFOOT)
		return;

	// Store player position
	if (!pBitStream->Read((char *)&m_vecPosition, sizeof(CVector3)))
		return;

	// Set the sync flag
	m_bHasSync = true;
}

