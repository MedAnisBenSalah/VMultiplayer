/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Game.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CGame::CGame()
{
	// Reset pointers
	m_pPedFactory = NULL;
	m_pThreadManager = NULL;
	m_pGtaThread = NULL;
}

CGame::~CGame()
{
	// Delete the pointers
	SAFE_DELETE(m_pThreadManager);
	SAFE_DELETE(m_pPedFactory);
}

void CGame::Initialize()
{
	// Install hooks
	CHooks::InstallGameHooks();
	// Install Patches
	CPatches::InstallPatches();
}

void CGame::DoGameLoad()
{
	// Initialize pools
	CVPools::Initialize();
	// Create ped factory instance
	m_pPedFactory = new CVPedFactory(*(VPedFactory **)CAddress::PTR_PedFactory);
	// Create thread manager instance
	m_pThreadManager = new CVThreadManager(*(VThreadManager **)CAddress::PTR_ThreadManager);
	// Initial update for the thread manager
	m_pThreadManager->Update(*(WORD *)CAddress::VAR_ThreadsCount);
	// Create our thread
	m_pGtaThread = m_pThreadManager->CreateThread(NAME);
}

void CGame::BeginProcess(VGtaThread *pThread)
{
	// Update the thread manager
	m_pThreadManager->Update(*(WORD *)CAddress::VAR_ThreadsCount);
	// Get the current TEB
	DWORD dwTlsIndex = *(DWORD *)CAddress::VAR_TlsIndex;
	DWORD64 dwTEB = GetTEB(dwTlsIndex);
	// Set the current thread
	*(VGtaThread **)(dwTEB + 0x830) = pThread;
	// Set the current thread state to be active
	*(BYTE *)(dwTEB + 0x838) = 1;
	// Set the current thread pointer
	*(VGtaThread **)CAddress::PTR_CurrentThread = pThread;
}

void CGame::EndProcess(VGtaThread *pThread)
{
	// Get the current TEB
	DWORD dwTlsIndex = *(DWORD *)CAddress::VAR_TlsIndex;
	DWORD64 dwTEB = GetTEB(dwTlsIndex);
	// Set the current thread
	*(VGtaThread **)(dwTEB + 0x830) = pThread;
	// Set the current thread state to be inactive
	*(BYTE *)(dwTEB + 0x838) = 0;
	// Set the current thread pointer
	*(VGtaThread **)CAddress::PTR_CurrentThread = pThread;
}