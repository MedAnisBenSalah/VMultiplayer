/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Player.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Player class source file
=============================================================*/

#include "Main.h"

// Prototype for CPed__Destructor
typedef void(*CPed__Destructor_t)(VPed *pPed, DWORD dwKeepInPool);

CNetworkPlayer::CNetworkPlayer(bool bLocal, int iPlayerId, char *szPlayerName)
{
	// Save the local player indication flag
	m_bLocal = bLocal;
	// Save player id
	m_iPlayerId = iPlayerId;
	// Save player name
	strcpy(m_szPlayerName, szPlayerName);
	// Set state
	m_state = PLAYER_STATE_CONNECTED;
	// Reset pointers
	m_pPed = NULL;
	m_pPlayerInfo = NULL;
	m_pModel = NULL;
}

CNetworkPlayer::~CNetworkPlayer()
{
	// Reset player state
	m_state = PLAYER_STATE_DISCONNECTED;
	// Delete player info instance
	SAFE_DELETE(m_pPlayerInfo);
	// Delete player ped instance
	SAFE_DELETE(m_pPed);
	// Delete model instance
	SAFE_DELETE(m_pModel);
}

bool CNetworkPlayer::Create()
{
	LOG("CNetworkPlayer::Create");
	// Make sure it is not the local player
	if(m_bLocal)
		return false;

	// If we don't have a player model instance then create it
	if (!m_pModel)
	{
		LOG("CNetworkPlayer::Create - Creating new model instance");
		// Create the model instance
		m_pModel = new CModel(CVGame::GetKeyHash("player_zero"));
		// Make sure the model instance is created
		if (!m_pModel)
			return false;

		// Load the player model
		if (!m_pModel->Load())
			return false;

		LOG("CNetworkPlayer::Create - Model instance created");
	}
	else
	{
		// Update the model hash
		if (!m_pModel->SetHash(CVGame::GetKeyHash("player_zero")))
			return false;
	}
	LOG("CNetworkPlayer::Create - Model setup");
	// If we don't have a player info for this player
	if (!m_pPlayerInfo)
	{
		LOG("CNetworkPlayer::Create - Creating player info");
		// Create the player info
		VPlayerInfo *pPlayerInfo = CVPools::GetPlayerInfoPool()->Allocate();
		if (!pPlayerInfo)
			return false;

		// Call the player info constructor
		if (!CAddress::FUNC_CPlayerInfo__Constructor(pPlayerInfo, 0, 0))
			return false;

		// Create the player info instance
		m_pPlayerInfo = new CVPlayerInfo(pPlayerInfo);
		LOG("CNetworkPlayer::Create - Player info created");
	}
	// Create the player ped
	VPed *pPed = CVPools::GetPedPool()->Allocate();
	if (!pPed)
		return false;

	LOG("CNetworkPlayer::Create - Crated ped (0x%lp)", pPed);
	// Get the player model info
	VModelInfo modelInfo;
	m_pModel->GetModelInfo(&modelInfo);
	LOG("CNetworkPlayer::Create - Found model info (0x%lp)", &modelInfo);
	// Call the ped constructor
	if (!CAddress::FUNC_CPed__Constructor(pPed, 16, (DWORD64)&modelInfo, 0x1A53))
		return false;

	LOG("CNetworkPlayer::Create - Created ped");
	// Create the ped instance
	m_pPed = new CVPed(pPed);
	// Set the ped player info
	m_pPed->SetPlayerInfo(m_pPlayerInfo->GetInterface());
	// Set the player info ped
	m_pPlayerInfo->SetPed(m_pPed->GetInterface<VPed>());
	// Setup the ped IK manager
	CAddress::FUNC_CPed__SetupIKManager(pPed, &modelInfo);
	// Set the IKManager ped to this ped
	pPed->pIKManager->pPed = pPed;
	// Set his name
	//m_pPlayerInfo->GetInterface()->pPlayerUnknown->szName = (char *)malloc(16);
	//strcpy(m_pPlayerInfo->GetInterface()->pPlayerUnknown->szName, m_szPlayerName);
	LOG("CNetworkPlayer::Create End");

	return true;
}

void CNetworkPlayer::Spawn()
{
	LOG("CNetworkPlayer::Spawn");
	// Spawn the player
	m_pPed->SpawnAt(CVector3(-785.790100f, -50.124935f, 37.733742f));
	// Set the player model
	SetModel(CVGame::GetKeyHash("player_zero"));
	// Set state
	m_state = PLAYER_STATE_ONFOOT;

	LOG("CNetworkPlayer::Spawn End");
}

void CNetworkPlayer::Destroy()
{
	// Get the ped VF table
	/*DWORD64 dwPed = (DWORD64)(GetPed()->GetInterface<VPed>());
	DWORD64 dwPedVFTable = *(DWORD64 *)(dwPed);*/
	// Call CPed__Destructor
	CPed__Destructor_t CPed__Destructor = (CPed__Destructor_t)(CCore::GetBaseAddress() + 0x1402CF934);
	CPed__Destructor(GetPed()->GetInterface<VPed>(), 0);
}

void CNetworkPlayer::SetModel(DWORD dwModelHash)
{
	LOG("CNetworkPlayer::SetModel(0x%x)", dwModelHash);
	if (!m_pModel)
	{
		LOG("CNetworkPlayer::SetModel - No instance found");
		// Create the model instance
		m_pModel = new CModel(dwModelHash);
		// Make sure the model instance is created
		if (!m_pModel)
			return;

		LOG("CNetworkPlayer::SetModel - Created new instance");
		// Load the player model
		if (!m_pModel->Load())
			return;

		LOG("CNetworkPlayer::SetModel - Model loaded");
	}
	else
	{
		// Update the model hash
		if (!m_pModel->SetHash(CVGame::GetKeyHash("player_zero")))
			return;
	}
	// Get the model info
	VModelInfo modelInfo;
	m_pModel->GetModelInfo(&modelInfo);
	LOG("CNetworkPlayer::SetModel - Found model info 0x%lp", &modelInfo);
	// Set the ped model
	m_pPed->SetModel(&modelInfo);
	LOG("CNetworkPlayer::SetModel End");
}
