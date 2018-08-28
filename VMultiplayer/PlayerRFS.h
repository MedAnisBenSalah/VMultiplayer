/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerRFS.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef PLAYERRFS_H
#define PLAYERRFS_H

class CPlayerRFS
{
public:
	static void RegisterRFS(CNetwork *pNetwork);

	static void Join(CRFParameters *pRFParameters);
	static void Leave(CRFParameters *pRFParameters);
	static void Spawn(CRFParameters *pRFParameters);
};

#endif