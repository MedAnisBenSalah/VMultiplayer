/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Model.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CModel::CModel(DWORD dwModelHash)
{
	// Set the model hash
	m_dwModelHash = dwModelHash;
	// TODO: Find how to get model from hash
}

CModel::~CModel()
{

}

bool CModel::Load()
{
	if (IsLoaded())
		return true;

	// Request the model
	CVStreaming::RequestModel(m_dwModelHash);
	// Get the initial tick
	DWORD64 dwStartTick = GetTickCount64();
	// Wait until the model is loaded
	while (!CVStreaming::HasModelLoaded(m_dwModelHash) && (GetTickCount64() - dwStartTick) < 2000)
		Sleep(0);

	return IsLoaded();
}

bool CModel::IsLoaded()
{
	return CVStreaming::HasModelLoaded(m_dwModelHash);
}

bool CModel::SetHash(DWORD dwModelHash)
{
	// Set the model hash
	m_dwModelHash = dwModelHash;
	// Reload it
	return Load();
}

void CModel::GetModelInfo(VModelInfo *pModelInfo)
{
	// Get the model info and return it
	CVStreaming::GetModelInfoFromHash(m_dwModelHash, pModelInfo);
}
