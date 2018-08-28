/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Component.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#ifndef COMPONENT_H
#define COMPONENT_H

#ifdef _WIN32
#	include <Windows.h>
#endif
#include <Common.h>
#include <Library.h>

class CComponent
{
public:
	CComponent(char *szName);
	~CComponent();

	void GetName(char *szName) { strcpy(szName, m_szName); };
	char *GetName() { return (char *)&m_szName; };

	bool Load();
	void Unload();
	bool IsLoaded() { return m_bLoaded; };

	template <typename T>
	T	GetInitializeAddress() { return (T)m_pAddress; };

private:
	bool			m_bLoaded;
	char			m_szName[MAX_PATH];
	CLibrary		*m_pLibrary;
	void			*m_pAddress;
};

#endif