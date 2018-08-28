/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Component.cpp
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#include "Component.h"
#include <SharedUtility.h>

CComponent::CComponent(char *szName)
{
	// Save the component name
	strcpy(m_szName, szName);
	// Reset flags
	m_pLibrary = NULL;
	m_pAddress = NULL;
	m_bLoaded = false;
}

CComponent::~CComponent()
{
	// Unload
	Unload();
}

bool CComponent::Load()
{
	// Make sure we are not loaded yet
	if (m_bLoaded)
		return true;

	// Get the full path
	char szPath[MAX_PATH], szLibraryPath[MAX_PATH];
	CSharedUtility::GetCurrentLibraryPath(VMULTIPLAYER_LIBRARY, szPath);
	sprintf(szLibraryPath, "%s\\VMultiplayer%s.dll", szPath, m_szName);
	// Load the module
	m_pLibrary = new CLibrary(szLibraryPath);
	if (!m_pLibrary || !m_pLibrary->Load())
		return false;

	// Create the function name
	char szFunctionName[128];
	sprintf(szFunctionName, "VMultiplayer_Create%s", m_szName);
	// Get the initializing funtion address
	m_pAddress = (void *)m_pLibrary->GetProcedureAddress(szFunctionName);
	if (!m_pAddress)
	{
		// Unload the library
		m_pLibrary->Unload();
		SAFE_DELETE(m_pLibrary);
		return false;
	}
	return true;
}

void CComponent::Unload()
{
	// Make sure we are loaded
	if (!m_bLoaded)
		return;

	// Unload the library
	m_pLibrary->Unload();
	SAFE_DELETE(m_pLibrary);
}