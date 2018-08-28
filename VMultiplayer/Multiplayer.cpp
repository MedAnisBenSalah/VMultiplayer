/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Multiplayer.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CMultiplayer::CMultiplayer()
{
	// Enable input by default
	m_bInputState = true;
}

CMultiplayer::~CMultiplayer()
{

}

bool CMultiplayer::Initialize()
{
	return true;
}
/*
void CMultiplayer::InitializeGraphics(ID3D11Device *pDevice, int iWidth, int iHeight)
{
	LOG("CMultiplayer::InitializeGraphics(0x%x)", pDevice);
	// Save the device pointer
	m_pDevice = pDevice;
	// Create the graphics
	m_pGraphics = new CGraphics();
	if (!m_pGraphics || !m_pGraphics->Initialize(iWidth, iHeight, pDevice))
	{
		MessageBox(NULL, "Failed to initialize graphics.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Register the input callback
	m_pGraphics->GetChatWindow()->GetChatButton()->RegisterButtonCallback(&CMultiplayer::ParseInput);

	LOG("CMultiplayer::InitializeGraphics Done");
}

void CMultiplayer::InitializeClient(char *szHost, int iPort, char *szPassword, int iPasswordLength)
{
	LOG("CMultiplayer::InitializeClient(%d)", iPort);
	// Create the graphics
	m_pClient = new CClient(szHost, iPort, szPassword, iPasswordLength);
	if (!m_pClient || !m_pClient->Initialize())
	{
		MessageBox(NULL, "Failed to initialize client.", "V:Multiplayer Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	LOG("CMultiplayer::InitializeClient Done");
}*/

void CMultiplayer::Process()
{	
	// Update the local player pointer
	if (CCore::GetLocalPlayer())
		CCore::GetLocalPlayer()->GetPed()->SetInterface(CCore::GetGame()->GetPedFactory()->GetLocalPlayer());
}

void CMultiplayer::ChangeInputState()
{
	// Toggle the input window depending on its current state
	if (CCore::GetGraphics()->GetChatWindow()->IsInputEnabled())
	{
		// Toggle the cursor off
		CCore::GetGraphics()->GetGUI()->ToggleCursor(false);
		// Toggle it off
		CCore::GetGraphics()->GetChatWindow()->ToggleInput(false);
		// Restore player's input
		ToggleInput(true);
	}
	else
	{
		// Toggle the cursor on
		CCore::GetGraphics()->GetGUI()->ToggleCursor(true);
		// Toggle it on
		CCore::GetGraphics()->GetChatWindow()->ToggleInput(true);
		// Disable player's input
		ToggleInput(false);
	}
}

void CMultiplayer::ParseInput()
{
	char szText[MAX_MESSAGE_LENGTH];
	CCore::GetGraphics()->GetChatWindow()->GetChatInput()->GetText(szText);
	// Reset the editbox text
	CCore::GetGraphics()->GetChatWindow()->GetChatInput()->SetText("");
	// Toggle the chatinput off
	CCore::GetMultiplayer()->ChangeInputState();
	// Send the chat text
	BitStream bsSend;
	bsSend.Write(szText);
	CCore::GetClient()->GetNetwork()->InvokeRF(eRFIdentifier::ID_RF_CHAT_MESSAGE, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, INVALID_NETWORK_ID, true);
}