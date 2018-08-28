/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: ConnectWindow.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

class CConnectWindow
{
public:
	CConnectWindow(CGUI *pGUI);
	~CConnectWindow();

	bool	Initialize(int iWidth, int iHeight);
	void	Toggle(bool bToggle);
	bool	IsVisible();
	void	SetText(char *szText, ...);

	CGUIText	*GetText() { return m_pText; };


private:
	bool							m_bInitialized;
	CGUI							*m_pGUI;
	CGUIWindow						*m_pMainWindow;
	CGUIText						*m_pText;
};

#endif