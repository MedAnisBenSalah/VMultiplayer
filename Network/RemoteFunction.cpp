/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: RFManager.cpp
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace RakNet;

CRemoteFunction::CRemoteFunction(int iRFId, RemoteFunctionInvoke_t pfnCallback)
{
	// Save the RF parameters
	m_iLocalId = iRFId;
	m_pfnCallback = pfnCallback;
}

CRemoteFunction::~CRemoteFunction()
{

}

void CRemoteFunction::Invoke(CRFParameters *pRFParameters)
{
	// Call the RF callback
	if (m_pfnCallback)
		m_pfnCallback(pRFParameters);
}



