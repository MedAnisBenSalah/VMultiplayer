/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerManager.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CPlayerManager::CPlayerManager() : CManagerBase(MAX_PLAYERS)
{

}

CPlayerManager::~CPlayerManager()
{
	// Reset all
	Reset();
}

bool CPlayerManager::AddPlayer(int iPlayerId, char *szName)
{
	// Create a new player instance
	CNetworkPlayer *pPlayer = new CNetworkPlayer(false, iPlayerId, szName);
	if (!pPlayer)
		return false;

	// Create the player
	if (!pPlayer->Create())
		return false;

	// Add the player to the manager
	Add(pPlayer, iPlayerId);
	return true;
}

void CPlayerManager::RemovePlayer(int iPlayerId)
{
	// Validate the player
	if (!IsValid(iPlayerId) && !GetAt(iPlayerId))
		return;

	// Delete the player
	CNetworkPlayer *pPlayer = GetAt(iPlayerId);
	pPlayer->Destroy();
	SAFE_DELETE(pPlayer);
	// Delete the player from manager
	Remove(iPlayerId);
}

void CPlayerManager::Reset()
{
	// Loop through all the players
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		// Validate the player
		if (IsValid(i) && GetAt(i))
			RemovePlayer(i);
	}
}