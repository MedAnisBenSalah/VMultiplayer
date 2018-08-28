/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerRFS.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

void CPlayerRFS::RegisterRFS(CNetwork *pNetwork)
{
	pNetwork->RegisterRemoteFunction((int)eRFIdentifier::ID_RF_PLAYER_JOIN, Join);
	pNetwork->RegisterRemoteFunction((int)eRFIdentifier::ID_RF_PLAYER_LEAVE, Leave);
	pNetwork->RegisterRemoteFunction((int)eRFIdentifier::ID_RF_PLAYER_SPAWN, Spawn);
}

void CPlayerRFS::Join(CRFParameters *pRFParameters)
{
	LOG("CPlayerRFS::Join");
	// Get player id
	int iPlayerId = INVALID_NETWORK_ID;
	if (!pRFParameters->GetBitStream()->Read(iPlayerId))
		return;

	LOG("CPlayerRFS::Join - PlayerId: %d", iPlayerId);
	// Validate sender info
	if (iPlayerId >= MAX_PLAYERS || iPlayerId < 0)
		return;

	// Get the player name
	char szPlayerName[MAX_NAME_LENGTH];
	if (!pRFParameters->GetBitStream()->Read(szPlayerName))
		return;

	LOG("CPlayerRFS::Join - PlayerName: %s", szPlayerName);
	// Read the spawned flag
	bool bIsSpawned = false;
	if (!pRFParameters->GetBitStream()->Read(bIsSpawned))
		return;

	LOG("CPlayerRFS::Join - IsSpawned: %s", bIsSpawned ? "yes" : "no");
	// Add the player to the player manager
	if (!CCore::GetPlayerManager()->AddPlayer(iPlayerId, szPlayerName))
		return;

	LOG("CPlayerRFS::Join - Player added");
	// Spawn the player
	if (bIsSpawned)
		CCore::GetPlayerManager()->GetAt(iPlayerId)->Spawn();

	LOG("CPlayerRFS::Join End");
}

void CPlayerRFS::Leave(CRFParameters *pRFParameters)
{
	LOG("CPlayerRFS::Leave");
	// Get player id
	int iPlayerId = INVALID_NETWORK_ID;
	if (!pRFParameters->GetBitStream()->Read(iPlayerId))
		return;

	LOG("CPlayerRFS::Leave - PlayerID: %d", iPlayerId);
	// Validate sender info
	if (iPlayerId >= MAX_PLAYERS || iPlayerId < 0)
		return;

	// Destroy the player
	CCore::GetPlayerManager()->RemovePlayer(iPlayerId);
	LOG("CPlayerRFS::Leave End");
}

void CPlayerRFS::Spawn(CRFParameters *pRFParameters)
{
	LOG("CPlayerRFS::Spawn");
	// Get player id
	int iPlayerId = INVALID_NETWORK_ID;
	if (!pRFParameters->GetBitStream()->Read(iPlayerId))
		return;

	LOG("CPlayerRFS::Spawn - PlayerId: %d", iPlayerId);
	// Validate sender info
	if (iPlayerId >= MAX_PLAYERS || iPlayerId < 0)
		return;

	// Spawn the player
	if (iPlayerId == CCore::GetLocalPlayer()->GetId())
	{
		LOG("CPlayerRFS::Spawn - Spawning local player");
		CCore::GetLocalPlayer()->Spawn();
		// Unfade the camera
		CVGame::FadeScreen(VSCREEN_FADE_TYPE_OUT, 0);
		// Hide the connecting window
		CCore::GetGraphics()->GetConnectWindow()->Toggle(false);
		// Show chat window
		CCore::GetGraphics()->GetChatWindow()->Toggle(true);
		// Set client state
		CCore::GetClient()->SetState(CLIENT_STATE_PLAYING);
		LOG("CPlayerRFS::Spawn - Local player spawned");
	}
	else
		CCore::GetPlayerManager()->GetAt(iPlayerId)->Spawn();

	LOG("CPlayerRFS::Spawn End");
}