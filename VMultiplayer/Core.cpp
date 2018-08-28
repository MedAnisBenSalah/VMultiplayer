/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Core.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

// Member variables
HWND			CCore::m_hWindow = NULL;
ID3D11Device	*CCore::m_pDevice = NULL;
DWORD64			CCore::m_dwBaseAddress = NULL;
CComponent		*CCore::m_pGUIComponent = NULL;
CComponent		*CCore::m_pNetworkComponent = NULL;
CThread			*CCore::m_pLoadingThread = NULL;
CMultiplayer	*CCore::m_pMultiplayer = NULL;
CGame			*CCore::m_pGame = NULL;
CGraphics		*CCore::m_pGraphics = NULL;
CClient			*CCore::m_pClient = NULL;
CLocalPlayer	*CCore::m_pLocalPlayer = NULL;
CPlayerManager	*CCore::m_pPlayerManager = NULL;

// TODO: Move it somewhere else or simply clean it
#define C_CPopulation__CreatePed "\x48\x8B\xC4\x48\x89\x58\x18\x4C\x89\x48\x20\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\xC1\x48\x81\xEC\xD0\x00\x00\x00"

bool CCore::IsGameReady()
{
	// Try to find some random patterns to check if the game is unpacked yet
	if (!CUtility::FindPattern(C_CPopulation__CreatePed, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"))
		return false;

	return true;
}

void CCore::Initialize()
{
	// Find VMultiplayer path
	char szPath[MAX_PATH];
	CSharedUtility::GetCurrentLibraryPath(VMULTIPLAYER_LIBRARY, szPath);
	// Install the exception handler
	CExceptionHandler::Install(szPath);
	// Get the module base address
	m_dwBaseAddress = (DWORD64)GetModuleHandle(NULL) - 0x13FBC0000;
	// Create instances
	m_pMultiplayer = new CMultiplayer();
	m_pGame = new CGame();
	m_pGraphics = new CGraphics(m_pGUIComponent);
	m_pClient = new CClient(m_pNetworkComponent);
	m_pLocalPlayer = new CLocalPlayer("");
	m_pPlayerManager = new CPlayerManager();
	// Install hooks
	CHooks::InstallAPIHooks();
	// Create the loading thread
	m_pLoadingThread = new CThread(LoadingThread);
	if (!m_pLoadingThread->Start())
		CUtility::ExitWithError("Failed to load the game.");
}

void CCore::LoadComponents()
{
	// Load the GUI component
	m_pGUIComponent = new CComponent("GUI");
	if (!m_pGUIComponent || !m_pGUIComponent->Load())
	{
		CUtility::ExitWithError("Failed to load the GUI component\nPlease re-install "NAME" or visit the website at "WEBSITE".");
		return;
	}
	// Load the network component
	m_pNetworkComponent = new CComponent("Network_x64");
	if (!m_pNetworkComponent || !m_pNetworkComponent->Load())
	{
		CUtility::ExitWithError("Failed to load the network component\nPlease re-install "NAME" or visit the website at "WEBSITE".");
		return;
	}
}

void CCore::LoadSettings()
{
	// Set the client connection target
	m_pClient->SetConnectTarget("127.0.0.1", 5555, "", 0);
	// Set local player name
	m_pLocalPlayer->SetName("OrMisicL");
}

void CCore::Quit()
{
	// Delete all instances
	SAFE_DELETE(m_pMultiplayer);
	SAFE_DELETE(m_pGame);
	SAFE_DELETE(m_pGraphics);
	SAFE_DELETE(m_pClient);
	SAFE_DELETE(m_pLocalPlayer);
	SAFE_DELETE(m_pPlayerManager);
}

void CCore::Process()
{
	// Process multiplayer
	if (m_pMultiplayer)
		m_pMultiplayer->Process();

	// Process client
	if (m_pClient)
		m_pClient->Process();

	// Process local player
	if (m_pLocalPlayer)
		m_pLocalPlayer->ProcessSync();
}

void CCore::OnGameLoad()
{
	// Initialize memory addresses
	CAddress::Initialize(m_dwBaseAddress);
	// Initialize the game
	m_pGame->Initialize();
}

void CCore::OnGameStart()
{
	// Do game load
	m_pGame->DoGameLoad();
	// Set the local player interface
	m_pLocalPlayer->SetInterface(m_pGame->GetPedFactory()->GetLocalPlayer());
	// Initialize client
	m_pClient->Initialize();
}

void CCore::ResetForReconnection()
{
	// Reset player manager
	m_pPlayerManager->Reset();
	// Toggle input off
	m_pMultiplayer->ToggleInput(false);
	// Hide chatwindow
	m_pGraphics->GetChatWindow()->Toggle(false);
	// Show connection window
	m_pGraphics->GetConnectWindow()->Toggle(true);
}

void CCore::LoadingThread(void *pThread)
{
	LOG("LoadingThread started.");
	// Keep looping until we initialize ourselves
	while (true)
	{
		// Check if the game is ready to load
		if (!CCore::IsGameReady())
			Sleep(5);
		else
		{
			// Load the game
			CCore::OnGameLoad();
			break;
		}
	}
	LOG("LoadingThread ended.");
	// Kill ourselves
	reinterpret_cast<CThread *>(pThread)->Kill();
}