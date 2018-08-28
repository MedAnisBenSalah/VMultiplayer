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
		CNetworkPlayer(bool bLocal, int iPlayerId, char *szPlayerName);
		~CNetworkPlayer();
		
		void SetId(int iPlayerId) { m_iPlayerId = iPlayerId; };
		int  GetId() { return m_iPlayerId; };

		void SetName(char *szName) { strcpy(m_szPlayerName, szName); };
		void GetName(char *szName) { strcpy(szName, m_szPlayerName); };
		
		bool Create();
		void Spawn();
		void SetModel(DWORD dwModelHash);
		void Destroy();

		ePlayerState	GetState() { return m_state; };
		void SetState(ePlayerState state) { m_state = state; };

		// Ped handle
		void SetPed(CVPed *pPed)
		{
			// do we have a valid pointer ?
			if (pPed)
				// Set player ped pointer
				m_pPed = pPed;
		};
		CVPed *GetPed() { return m_pPed; };

		// PlayerInfo handle
		void SetPlayerInfo(CVPlayerInfo *pPlayerInfo)
		{
			// do we have a valid pointer ?
			if(pPlayerInfo)
				// Set player ped pointer
				m_pPlayerInfo = pPlayerInfo;
		};
		CVPlayerInfo *GetPlayerInfo() { return m_pPlayerInfo; }; 

		// Model handle
		void SetModelInterface(CModel *pModel)
		{
			// do we have a valid pointer ?
			if (pModel)
				// Set player ped pointer
				m_pModel = pModel;
		};
		CModel *GetModelInterface() { return m_pModel; };

	private:
		bool					m_bLocal;
		int						m_iPlayerId;
		char					m_szPlayerName[MAX_NAME_LENGTH];
		ePlayerState			m_state;
		CVPed					*m_pPed;
		CVPlayerInfo			*m_pPlayerInfo;
		CModel					*m_pModel;
		
};

#endif