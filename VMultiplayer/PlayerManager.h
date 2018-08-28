/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerManager.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

class CPlayerManager : public CManagerBase<CNetworkPlayer>
{
public:
	CPlayerManager();
	~CPlayerManager();

	bool AddPlayer(int iPlayerId, char *szName);
	void RemovePlayer(int iPlayerId);
	void Reset();
	void Process();

private:

};

#endif