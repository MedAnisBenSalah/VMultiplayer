/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Client.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

#define CLIENT_RECONNECT_TIME	3000 // 3 secondes between each connection attempt

typedef CNetwork *(*VMultiplayer_CreateNetwork_t)(bool bIsServer);
VMultiplayer_CreateNetwork_t		pfnVMultiplayer_CreateNetwork = NULL;

CClient::CClient(CComponent *pComponent)
{
	// Set th component
	m_pComponent = pComponent;
	// Reset flags
	m_bInitialized = false;
	// Set the last connection tick
	m_dwLastConnectionTick = GetTickCount64();
}

CClient::~CClient()
{

}

void CClient::SetConnectTarget(char *szHost, int iPort, char *szPassword, int iPasswordLength)
{
	// Set parameters
	strcpy(m_szHost, szHost);
	strcpy(m_szPassword, szPassword);
	m_iPort = iPort;
	m_iPasswordLength = iPasswordLength;
}

bool CClient::Initialize()
{
	// Make sure we are not already initialized
	if (m_bInitialized)
		return true;

	// Get the initializing funtion address
	pfnVMultiplayer_CreateNetwork = m_pComponent->GetInitializeAddress<VMultiplayer_CreateNetwork_t>();
	if (!pfnVMultiplayer_CreateNetwork)
		return false;

	// Create the network instance
	m_pNetwork = pfnVMultiplayer_CreateNetwork(false);
	// Try to initialize the network
	if (!m_pNetwork->Initialize(m_iPort, 0))
		return false;

	// Set the client state
	m_state = CLIENT_STATE_WAITING_CONNECTION;
	// Register RFS
	CMainRFS::RegisterRFS(m_pNetwork);
	CPlayerRFS::RegisterRFS(m_pNetwork);
	// Flag as initialized
	m_bInitialized = true;
	return true;
}

bool CClient::Connect()
{
	// Try to connect
	if (!m_pNetwork->Connect(m_szHost, m_iPort, m_szPassword, m_iPasswordLength))
		return false;

	return true;
}

void CClient::Process()
{
	// Process the client according to its state
	switch (m_state)
	{
		// Waiting to send a connection request	
		case CLIENT_STATE_WAITING_CONNECTION:
			// Make sure we waited long enough before re-attempting to connect
			if ((GetTickCount64() - m_dwLastConnectionTick) >= CLIENT_RECONNECT_TIME)
			{
				// Try to connect
				if (Connect())
				{
					// Update the client state
					m_state = CLIENT_STATE_CONNECTING;
					// Update the connection text
					CCore::GetGraphics()->GetConnectWindow()->SetText("Connecting to %s:%d ...", m_szHost, m_iPort);
				}
				else
				{
					// Update the connection text
					CCore::GetGraphics()->GetConnectWindow()->SetText("Failed to send the connection request. Retrying ...");
					// Update the connection tick
					m_dwLastConnectionTick = GetTickCount64();
				}
			}

			break;
	}
	// Update the network
	if (m_state != CLIENT_STATE_WAITING_CONNECTION && m_state != CLIENT_STATE_DISCONNECTED)
		UpdateNetwork();
}

void CClient::UpdateNetwork()
{
	// Update the network
	CNetMessage *pMessage = m_pNetwork->Process();
	if (!pMessage)
		return;

	// Process each message
	switch (pMessage->GetMessageID())
	{
		// On connection failed
	case ID_CONNECTION_ATTEMPT_FAILED:
		OnConnectionFailed();
		break;

		// Connection accepted
	case ID_CONNECTION_REQUEST_ACCEPTED:
		OnConnectionAccepted();
		break;

		// On lost connection
	case ID_CONNECTION_LOST:
		OnConnectionLost();
		break;

	}
	// Deallocate the message
	m_pNetwork->DestroyMessage(pMessage);
}

void CClient::OnConnectionFailed()
{
	// Validate the state
	if (m_state != CLIENT_STATE_CONNECTING)
		return;

	// Update the text
	CCore::GetGraphics()->GetConnectWindow()->SetText("Connection attempt failed. Retrying ...");
	// Update the connection tick
	m_dwLastConnectionTick = GetTickCount64();
	// Set the state
	m_state = CLIENT_STATE_WAITING_CONNECTION;
}

void CClient::OnConnectionAccepted()
{
	// Validate the state
	if (m_state != CLIENT_STATE_CONNECTING)
		return;

	// Update the text
	CCore::GetGraphics()->GetConnectWindow()->SetText("Joining game ...");
	// Create the join request RF
	BitStream bsSend;
	// Write our name
	char szPlayerName[MAX_NAME_LENGTH];
	CCore::GetLocalPlayer()->GetName(szPlayerName);
	bsSend.Write(szPlayerName);
	// Invoke the player join RF
	m_pNetwork->InvokeRF(eRFIdentifier::ID_RF_PLAYER_JOIN, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, INVALID_NETWORK_ID, true);
	// Set the client state
	m_state = CLIENT_STATE_CONNECTED;
}

void CClient::OnConnectionLost()
{
	// Set the connection window text
	CCore::GetGraphics()->GetConnectWindow()->SetText("Connection was lost. Reconnecting ...");
	// Reset the core
	CCore::ResetForReconnection();
	// Update the connection tick
	m_dwLastConnectionTick = GetTickCount64();
	// Set the state
	m_state = CLIENT_STATE_WAITING_CONNECTION;
}