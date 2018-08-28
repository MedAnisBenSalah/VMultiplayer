/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerManager.cpp
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

extern CServer *pServer;

CPlayerManager::CPlayerManager() : CManagerBase(MAX_PLAYERS)
{

}

CPlayerManager::~CPlayerManager()
{

}

bool CPlayerManager::AddPlayer(int iPlayerId, char *szName)
{
	// Create a new player instance
	CNetworkPlayer *pPlayer = new CNetworkPlayer(iPlayerId, szName);
	if (!pPlayer)
		return false;

	// Add the player to the manager
	Add(pPlayer, iPlayerId);
	return true;
}

void CPlayerManager::RemovePlayer(int iPlayerId, eLeftReason reason)
{
	// Validate the player
	if (!IsValid(iPlayerId) && !GetAt(iPlayerId))
		return;

	// Get the player name
	char szPlayerName[MAX_NAME_LENGTH];
	GetAt(iPlayerId)->GetName(szPlayerName);
	// Delete the player
	CNetworkPlayer *pPlayer = GetAt(iPlayerId);
	SAFE_DELETE(pPlayer);
	// Delete the player from manager
	Remove(iPlayerId);
	// Broadcast the event
	BitStream bsSend;
	bsSend.Write(iPlayerId);
	pServer->GetNetwork()->InvokeRF(eRFIdentifier::ID_RF_PLAYER_LEAVE, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, INVALID_NETWORK_ID, true);
	// Get the left message
	char szLeftReason[32];
	switch (reason)
	{
	case LEFT_REASON_DISCONNECTED:
		strcpy(szLeftReason, "Disconnected");
		break;

	case LEFT_REASON_TIMEOUT:
		strcpy(szLeftReason, "Timed out");
		break;

	case LEFT_REASON_KICKED:
		strcpy(szLeftReason, "Kicked");
		break;

	case LEFT_REASON_BANNED:
		strcpy(szLeftReason, "Banned");
		break;
	}
	// Display the message
	LogPrintf("[ID: %d] %s has left the server (%s).", iPlayerId, szPlayerName, szLeftReason);
}

void CPlayerManager::Process()
{
	// Loop through all the players
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		// Validate the player
		if (IsValid(i) && GetAt(i))
			GetAt(i)->Process();
	}
}