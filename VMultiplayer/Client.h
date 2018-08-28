/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Client.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef CLIENT_H
#define CLIENT_H

enum eClientState
{
	CLIENT_STATE_WAITING_CONNECTION,
	CLIENT_STATE_CONNECTING,
	CLIENT_STATE_CONNECTED,
	CLIENT_STATE_JOINED,
	CLIENT_STATE_PLAYING,
	CLIENT_STATE_DISCONNECTED
};

class CClient
{
public:
	CClient(CComponent *pComponent);
	~CClient();

	void SetConnectTarget(char *szHost, int iPort, char *szPassword, int iPasswordLength);
	bool Initialize();
	bool Connect();
	void Process();
	void UpdateNetwork();

	CNetwork *GetNetwork() { return m_pNetwork; };
	eClientState GetState() { return m_state; };
	void SetState(eClientState state) { m_state = state; };

	// Events
	void OnConnectionFailed();
	void OnConnectionAccepted();
	void OnConnectionLost();


private:
	bool			m_bInitialized;
	eClientState	m_state;
	DWORD64			m_dwLastConnectionTick;
	char			m_szHost[128];
	int				m_iPort;
	char			m_szPassword[32];
	int				m_iPasswordLength;
	CComponent		*m_pComponent;
	CNetwork		*m_pNetwork;
};

#endif