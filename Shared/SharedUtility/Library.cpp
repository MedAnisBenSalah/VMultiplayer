/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Library.cpp
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#include "Library.h"

CLibrary::CLibrary(char *szLibrary)
{
	// Save library path
	strcpy(m_szPath, szLibrary);
	// Reset variables
	m_pHandle = NULL;
}

CLibrary::~CLibrary()
{
}

bool CLibrary::Load()
{
	// Try to load the library
#ifdef WIN32
	m_pHandle = LoadLibrary(m_szPath);
#else
	m_pHandle = dlopen(m_szPath, RTLD_LAZY);
#endif
	// Check the library load
	if(!m_pHandle)
		return false;
	else
		return true;
}

void CLibrary::Unload()
{
	if(!m_pHandle)
		return;
	// Try to unload the library
#ifdef WIN32
	FreeLibrary((HMODULE)m_pHandle);
#else
	dlclose(m_pHandle);
#endif

}

void *CLibrary::GetProcedureAddress(char *szProcName)
{
	if(!m_pHandle)
		return NULL;

	// Get the procedure address
	void *pAddress = NULL;

#ifdef WIN32
	pAddress = (void *)GetProcAddress((HMODULE)m_pHandle, szProcName);
#else
	pAddress = dlsym(m_pHandle, szProcName);
#endif

	return pAddress;
}

