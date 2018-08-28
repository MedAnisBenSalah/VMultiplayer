/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: MainRFS.cpp
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

extern CServer *pServer;

void CMainRFS::RegisterRFS(CNetwork *pNetwork)
{
	pNetwork->RegisterRemoteFunction((int)eRFIdentifier::ID_RF_CHAT_MESSAGE, ChatMessage);
}

void CMainRFS::ChatMessage(CRFParameters *pRFParameters)
{
	// Get player id
	int iPlayerId = pRFParameters->GetSenderInfo()->GetID();
	// Validate sender info
	if (iPlayerId >= MAX_PLAYERS || iPlayerId < 0)
		return;

	// Validate the player
	if (!pServer->GetPlayerManager()->IsValid(iPlayerId))
		return;

	// Get the player name
	char szChatMessage[MAX_MESSAGE_LENGTH];
	if (!pRFParameters->GetBitStream()->Read(szChatMessage))
		return;

	// TODO: When scripting is implemented, use it to send input to script
	// Send chat message
	BitStream bsSend;
	bsSend.Write(iPlayerId);
	bsSend.Write(szChatMessage);
	pServer->GetNetwork()->InvokeRF(eRFIdentifier::ID_RF_CHAT_MESSAGE, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, INVALID_NETWORK_ID, true);
	// Get player name
	char szPlayerName[MAX_NAME_LENGTH];
	pServer->GetPlayerManager()->GetAt(iPlayerId)->GetName(szPlayerName);
	LogPrintf("[ID: %d] CHAT(%s): %s", iPlayerId, szPlayerName, szChatMessage);
}