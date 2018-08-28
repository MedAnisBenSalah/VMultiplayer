/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: LocalPlayer.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/
#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

class CLocalPlayer : public CNetworkPlayer
{
	public:
		CLocalPlayer(char *szPlayerName);
		~CLocalPlayer();

		void SetInterface(VPed *pPed);
		void ProcessSync();

	private:
		DWORD64				m_dwLastTick;
};

#endif