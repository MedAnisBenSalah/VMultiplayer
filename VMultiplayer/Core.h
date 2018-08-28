/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Core.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef CORE_H
#define CORE_H

class CCore
{
public:
	static bool IsGameReady();
	static void Initialize();
	static void LoadSettings();
	static void LoadComponents();
	static void OnGameLoad();
	static void OnGameStart();
	static void Process();
	static void ResetForReconnection();
	static void Quit();

	static void					SetHWND(HWND hWnd) { m_hWindow = hWnd; };
	static HWND					GetHWND() { return m_hWindow; };
	static ID3D11Device			*GetDevice() { return m_pDevice; };
	static DWORD64				GetBaseAddress() { return m_dwBaseAddress; };
	static CThread				*GetLoadingThread() { return m_pLoadingThread; };
	static CMultiplayer			*GetMultiplayer() { return m_pMultiplayer; };
	static CGame				*GetGame() { return m_pGame; };
	static CGraphics			*GetGraphics() { return m_pGraphics; };
	static CClient				*GetClient() { return m_pClient; };
	static CLocalPlayer			*GetLocalPlayer() { return m_pLocalPlayer; };
	static CPlayerManager		*GetPlayerManager() { return m_pPlayerManager; };

protected:
	static void	LoadingThread(void *pThread);

private:
	static HWND						m_hWindow;
	static ID3D11Device				*m_pDevice;
	static DWORD64					m_dwBaseAddress;
	static CComponent				*m_pGUIComponent;
	static CComponent				*m_pNetworkComponent;
	static CThread					*m_pLoadingThread;
	static CMultiplayer				*m_pMultiplayer;
	static CGame					*m_pGame;
	static CGraphics				*m_pGraphics;
	static CClient					*m_pClient;
	static CLocalPlayer				*m_pLocalPlayer;
	static CPlayerManager			*m_pPlayerManager;
};

#endif