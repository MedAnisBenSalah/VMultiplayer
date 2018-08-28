/* =========================================================
       V:Multiplayer - http://www.vmultiplayer.com

-- File: Graphics.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

class CGraphics
{
public:
	CGraphics(CComponent *pComponent);
	~CGraphics();

	CGUI				*GetGUI() { return m_pGUI; };
	CChatWindow			*GetChatWindow() { return m_pChatWindow; };
	CConnectWindow		*GetConnectWindow() { return m_pConnectWindow; };

	bool	Initialize(int iWidth, int iHeight, ID3D11Device *pDevice);
	void	DoGameLoad();
	void    HandleInput(UINT uMsg, WPARAM wParam, LPARAM lParam);


private:
	bool							m_bInitialized;
	CComponent						*m_pComponent;
	CGUI							*m_pGUI;
	CGUIText						*m_pVersionText;
	CChatWindow						*m_pChatWindow;
	CConnectWindow					*m_pConnectWindow;
};

#endif