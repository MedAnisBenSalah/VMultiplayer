/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerManager.h
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

// Left reason enumeration
enum eLeftReason
{
	LEFT_REASON_TIMEOUT,
	LEFT_REASON_DISCONNECTED,
	LEFT_REASON_KICKED,
	LEFT_REASON_BANNED
};

class CPlayerManager : public CManagerBase<CNetworkPlayer>
{
public:
	CPlayerManager();
	~CPlayerManager();

	bool AddPlayer(int iPlayerId, char *szName);
	void RemovePlayer(int iPlayerId, eLeftReason reason);

	void Process();

private:

};

#endif