/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: MainRFS.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

void CMainRFS::RegisterRFS(CNetwork *pNetwork)
{
	pNetwork->RegisterRemoteFunction((int)eRFIdentifier::ID_RF_SETUP_WORLD, SetupWorld);
	pNetwork->RegisterRemoteFunction((int)eRFIdentifier::ID_RF_CHAT_MESSAGE, ChatMessage);
}

void CMainRFS::SetupWorld(CRFParameters *pRFParameters)
{
	// Get the local player id
	int iLocalId = INVALID_NETWORK_ID;
	if (!pRFParameters->GetBitStream()->Read(iLocalId))
		return;

	// Get the server name
	char szServerName[128];
	if (!pRFParameters->GetBitStream()->Read(szServerName))
		return;

	// Set local player ID
	CCore::GetLocalPlayer()->SetId(iLocalId);
	// Set the connection window text
	CCore::GetGraphics()->GetConnectWindow()->SetText("Awaiting spawn approval ...");
	// Request a spawn
	BitStream bsSend;
	CCore::GetClient()->GetNetwork()->InvokeRF(eRFIdentifier::ID_RF_PLAYER_SPAWN, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, INVALID_NETWORK_ID, true);
}

void CMainRFS::ChatMessage(CRFParameters *pRFParameters)
{
	// Get the player id
	int iPlayerId = INVALID_NETWORK_ID;
	if (!pRFParameters->GetBitStream()->Read(iPlayerId))
		return;

	// Get the player name
	char szChatMessage[MAX_MESSAGE_LENGTH];
	if (!pRFParameters->GetBitStream()->Read(szChatMessage))
		return;

	// Get player name
	char szName[MAX_NAME_LENGTH];
	if (iPlayerId == CCore::GetLocalPlayer()->GetId())
		CCore::GetLocalPlayer()->GetName(szName);
	else
		CCore::GetPlayerManager()->GetAt(iPlayerId)->GetName(szName);

	// Add the chat message
	CCore::GetGraphics()->GetChatWindow()->AddChatMessage(szChatMessage, szName);
}