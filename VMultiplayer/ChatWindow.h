/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: ChatWindow.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef CHATWINDOW_H
#define CHATWINDOW_H

class CChatWindow
{
public:
	CChatWindow(CGUI *pGUI);
	~CChatWindow();

	bool	Initialize(int iWidth, int iHeight);
	void	Toggle(bool bToggle);
	bool	IsVisible();
	void	ToggleInput(bool bToggle);
	bool	IsInputEnabled() { return m_bInputEnabled; };

	CGUIButton	*GetChatButton() { return m_pChatButton; };
	CGUIEditBox	*GetChatInput() { return m_pChatInput; };

	void AddChatMessage(char *szMessage, char *szPlayerName);


private:
	bool							m_bInitialized;
	bool							m_bInputEnabled;
	CGUI							*m_pGUI;
	//CGUIWindow						*m_pMainWindow;
	CGUIEditBox						*m_pMainWindow;
	CGUIEditBox						*m_pChatBox;
	CGUIEditBox						*m_pChatInput;
	CGUIButton						*m_pChatButton;
};

#endif