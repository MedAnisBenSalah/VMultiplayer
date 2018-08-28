/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerRFS.cpp
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

extern CServer		*pServer;

void CPlayerRFS::RegisterRFS(CNetwork *pNetwork)
{
	pNetwork->RegisterRemoteFunction((int)eRFIdentifier::ID_RF_PLAYER_JOIN, Join);
	pNetwork->RegisterRemoteFunction((int)eRFIdentifier::ID_RF_PLAYER_SPAWN, Spawn);
}

void CPlayerRFS::Join(CRFParameters *pRFParameters)
{
	// Get player id
	int iPlayerId = pRFParameters->GetSenderInfo()->GetID();
	// Validate sender info
	if (iPlayerId >= MAX_PLAYERS || iPlayerId < 0)
	{
		LogPrintf("Bad connection attempt from %s (ID: %d)", pRFParameters->GetSenderInfo()->GetIP(), iPlayerId);
		return;
	}
	// Get the player name
	char szPlayerName[MAX_NAME_LENGTH];
	if (!pRFParameters->GetBitStream()->Read(szPlayerName))
	{
		LogPrintf("Bad connection attempt from %s (ID: %d)", pRFParameters->GetSenderInfo()->GetIP(), iPlayerId);
		return;
	}
	// Add the player to the player manager
	if (!pServer->GetPlayerManager()->AddPlayer(iPlayerId, szPlayerName))
	{
		LogPrintf("Failed to join the player.");
		return;
	}
	// Add the player
	pServer->GetPlayerManager()->GetAt(iPlayerId)->AddForWorld();
	// Send the player all the active entities
	pServer->SendEntities(iPlayerId);
	// Send server information for the player
	BitStream bsSend;
	bsSend.Write(iPlayerId);
	bsSend.Write("Test server name");
	pServer->GetNetwork()->InvokeRF(eRFIdentifier::ID_RF_SETUP_WORLD, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, iPlayerId, false);

	LogPrintf("[ID: %d] %s has joined the server.", iPlayerId, szPlayerName);
}

void CPlayerRFS::Spawn(CRFParameters *pRFParameters)
{
	// Get player id
	int iPlayerId = pRFParameters->GetSenderInfo()->GetID();
	// Validate sender info
	if (iPlayerId >= MAX_PLAYERS || iPlayerId < 0)
		return;

	// TODO: When scripting is added do some callback invoking to handle spawning approval

	// Approve spawn request for player
	pServer->GetPlayerManager()->GetAt(iPlayerId)->SpawnForWorld();
	// Get player name
	char szPlayerName[MAX_NAME_LENGTH];
	pServer->GetPlayerManager()->GetAt(iPlayerId)->GetName(szPlayerName);
	LogPrintf("[ID: %d] Player (%s) has spawned.", iPlayerId, szPlayerName);
}