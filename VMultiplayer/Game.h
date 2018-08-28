/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Game.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef GAME_H
#define GAME_H

class CGame
{
public:
	CGame();
	~CGame();

	void Initialize();
	void DoGameLoad();

	void BeginProcess(VGtaThread *pThread);
	void EndProcess(VGtaThread *pThread);

	CVPedFactory		*GetPedFactory() { return m_pPedFactory; };
	CVThreadManager		*GetThreadManager() { return m_pThreadManager; };
	VGtaThread			*GetGtaThread() { return m_pGtaThread; };


private:
	CVPedFactory		*m_pPedFactory;
	CVThreadManager		*m_pThreadManager;
	VGtaThread			*m_pGtaThread;
};

#endif