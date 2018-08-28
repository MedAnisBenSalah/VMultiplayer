/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: NetworkPlayer.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H

#define MAX_NAME_LENGTH 32

class CNetworkPlayer
{
public:
	CNetworkPlayer(int iPlayerId, char *szPlayerName);
	~CNetworkPlayer();

	void SetName(char *szName) { strcpy(m_szPlayerName, szName); };
	void GetName(char *szName) { strcpy(szName, m_szPlayerName); };
	bool IsSpawned() { return m_bSpawned; };

	void AddForWorld();
	void AddForPlayer(int iPlayerId);
	void SpawnForWorld();

	void Process();

	ePlayerState	GetState() { return m_state; };
	void SetState(ePlayerState state) { m_state = state; };

	CVector3	GetPosition() { return m_vecPosition; };
	void SetPosition(CVector3 vecPosition) { m_vecPosition = vecPosition; };

	CVector3	GetVelocity() { return m_vecVelocity; };
	void SetVelocity(CVector3 vecVelocity) { m_vecVelocity = vecVelocity; };

	void StoreOnFootSyncData(BitStream *pBitStream);
	void StoreInVehicleSyncData(BitStream *pBitStream);

private:
	int						m_iPlayerId;
	char					m_szPlayerName[MAX_NAME_LENGTH];
	bool					m_bSpawned;
	ePlayerState			m_state;
	CVector3				m_vecPosition;
	CVector3				m_vecVelocity;
	float					m_fRotation;
	bool					m_bHasSync;
};

#endif