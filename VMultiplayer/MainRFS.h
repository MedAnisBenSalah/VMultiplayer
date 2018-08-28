/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: MainRFS.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef MAINRFS_H
#define MAINRFS_H

class CMainRFS
{
public:
	static void RegisterRFS(CNetwork *pNetwork);

	static void SetupWorld(CRFParameters *pRFParameters);
	static void ChatMessage(CRFParameters *pRFParameters);
};

#endif