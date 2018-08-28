/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VStreaming.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

typedef void(*RequestIPL_t)(char *szIPLName);
RequestIPL_t pfnRequestIPL = NULL;

char	CVStreaming::m_szIPLName[128];

void CVStreaming::RequestIPL(char *szIPLName)
{
	// Set the IPL name
	strcpy(m_szIPLName, szIPLName);
	// Request the IPL
	DWORD64 dwAddr = CCore::GetBaseAddress() + 0x140832870;
	pfnRequestIPL = (RequestIPL_t)dwAddr;
	pfnRequestIPL(m_szIPLName);
}

void CVStreaming::RequestModel(DWORD dwModelHash)
{
	// Request the model
	CAddress::FUNC_RequestModel(dwModelHash);
}

bool CVStreaming::HasModelLoaded(DWORD dwModelHash)
{
	// Check the model loaded
	return CAddress::FUNC_HasModelLoaded(dwModelHash);
}

void CVStreaming::GetModelInfoFromHash(DWORD dwModelHash, VModelInfo *pModelInfo)
{
	CAddress::FUNC_CStreaming__GetModelFromHash(dwModelHash, pModelInfo);
}