/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Library.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#ifndef LIBRARY_H
#define LIBRARY_H

#ifdef _WIN32
#include <windows.h>
#endif

class CLibrary
{
	public:
		CLibrary(char *szLibrary);
		~CLibrary();

		bool Load();
		void Unload();
		void *GetProcedureAddress(char *szProcName);

	private:
		char			m_szPath[MAX_PATH];
		void			*m_pHandle;
		

};

#endif
