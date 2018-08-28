/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Server.h
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#ifndef SERVER_H
#define SERVER_H

class CServer
{
public:
	CServer();
	~CServer();

	bool LoadComponents();
	bool Initialize(int iPort, int iMaxPlayers);
	bool Start(int iPort, int iMaxPlayers);
	void Process();
	void SendEntities(int iPlayerId);

	CNetwork		*GetNetwork() { return m_pNetwork; };
	CPlayerManager	*GetPlayerManager() { return m_pPlayerManager; };

private:
	bool				m_bInitialized;
	CComponent			*m_pNetworkComponent;
	CNetwork			*m_pNetwork;
	CPlayerManager		*m_pPlayerManager;
};

#endif