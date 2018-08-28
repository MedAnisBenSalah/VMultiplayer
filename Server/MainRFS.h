/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: MainRFS.h
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#ifndef MAINRFS_H
#define MAINRFS_H

class CMainRFS
{
public:
	static void RegisterRFS(CNetwork *pNetwork);

	static void Command(CRFParameters *pRFParameters);
	static void ChatMessage(CRFParameters *pRFParameters);
};

#endif