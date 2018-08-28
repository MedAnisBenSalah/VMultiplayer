/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: RFManager.cpp
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace RakNet;

CRFManager::CRFManager()
{
	// Clear the remote function's vector
	m_vectorRF.clear();
}

CRFManager::~CRFManager()
{
	// Loop through the RF vector
	for (std::vector<CRemoteFunction *>::iterator i = m_vectorRF.begin(); i != m_vectorRF.end(); i++)
		// Delete it
		SAFE_DELETE((*i));
	
	// Empty the RF vector
	m_vectorRF.clear();
}

void CRFManager::RegisterRemoteFunction(int iRFId, RemoteFunctionInvoke_t pfnCallback)
{
	// Create a new remote function instance
	CRemoteFunction *pRemoteFunction = new CRemoteFunction(iRFId, pfnCallback);
	if (!pRemoteFunction)
		return;

	// Add the function to the vector list
	m_vectorRF.push_back(pRemoteFunction);
}

void CRFManager::UnregisterRemoteFunction(int iRFId)
{
	// Find the RF
	CRemoteFunction *pRemoteFunction = NULL;
	int iId = Find(iRFId, &pRemoteFunction);
	if (!pRemoteFunction || iId == -1)
		return;

	// Remove from the vector
	m_vectorRF.erase(m_vectorRF.begin() + iId);
	// Delete the function object
	SAFE_DELETE(pRemoteFunction);
}

int CRFManager::Find(int iRFId, CRemoteFunction **ppReturnedRF)
{
	int iCount = 0;
	*ppReturnedRF = NULL;
	// Loop through the RF vector
	for (std::vector<CRemoteFunction *>::iterator i = m_vectorRF.begin(); i != m_vectorRF.end(); i++)
	{
		// Compare IDs
		if ((*i)->GetID() == iRFId)
		{
			*ppReturnedRF = (*i);
			return iCount;
		}
		else
			iCount++;
	}
	return -1;
}

void CRFManager::Invoke(int iRFId, CRFParameters *pRFParameters)
{
	// Find the RF
	CRemoteFunction *pRemoteFunction = NULL;
	int iId = Find(iRFId, &pRemoteFunction);
	if (!pRemoteFunction || iId == -1)
		return;

	// Invoke it
	pRemoteFunction->Invoke(pRFParameters);
}

