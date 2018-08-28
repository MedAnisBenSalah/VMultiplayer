/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: ChatWindow.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CChatWindow::CChatWindow(CGUI *pGUI)
{
	// Reset pointers
	m_pMainWindow = NULL;
	m_pChatBox = NULL;
	m_pChatInput = NULL;
	m_pChatButton = NULL;
	// Reset flags
	m_bInitialized = false;
	m_bInputEnabled = false;
	// Set the GUI pointer
	m_pGUI = pGUI;
}

CChatWindow::~CChatWindow()
{

}

bool CChatWindow::Initialize(int iWidth, int iHeight)
{
	LOG("CChatWindow::Initialize(0x%x)", m_pGUI);
	if (m_bInitialized)
		return true;

	// Load the layout
	if (!m_pGUI->LoadLayout(CHATWINDOW_LAYOUT))
		return false;

	// Find the main window
	m_pMainWindow = m_pGUI->FindGUIElement<CGUIEditBox>(GUI_ELEMENT_TYPE_EDITBOX, "ChatWindow_MainWindow");
	m_pChatBox = m_pGUI->FindGUIElement<CGUIEditBox>(GUI_ELEMENT_TYPE_EDITBOX, "ChatWindow_ChatBox");
	m_pChatInput = m_pGUI->FindGUIElement<CGUIEditBox>(GUI_ELEMENT_TYPE_EDITBOX, "ChatWindow_ChatInput");
	m_pChatButton = m_pGUI->FindGUIElement<CGUIButton>(GUI_ELEMENT_TYPE_BUTTON, "ChatWindow_SubmitButton");
	// Validate pointers
	if (!m_pMainWindow || !m_pChatBox || !m_pChatInput || !m_pChatButton)
		return false;

	// Set the chatwindow coordinates
	m_pMainWindow->SetPosition(CVector2(0.0f, 0.0f));
	m_pMainWindow->SetSize(CVector2((float)(iWidth / 3), (float)(iHeight / 3)));
	// Set the chat window propreties
	m_pMainWindow->SetAlpha(0.7f);
	m_pChatInput->SetAlpha(0.1f);
	m_pChatButton->SetAlpha(0.1f);
	// Mark as initialized
	m_bInitialized = true;
	LOG("CChatWindow::Initialize Done");
	return true;
}

void CChatWindow::Toggle(bool bToggle)
{
	m_pMainWindow->SetVisible(bToggle);
}

bool CChatWindow::IsVisible()
{
	return m_pMainWindow->IsVisible();
}

void CChatWindow::ToggleInput(bool bToggle)
{
	if (bToggle)
	{
		// Show it
		m_pChatInput->SetAlpha(0.7f);
		m_pChatButton->SetAlpha(0.7f);
		// Set focus
		m_pChatInput->SetFocus(true);
	}
	else
	{
		// Hide it
		m_pChatInput->SetAlpha(0.1f);
		m_pChatButton->SetAlpha(0.1f);
		// Remove focus
		m_pChatInput->SetFocus(false);
	}
	m_bInputEnabled = bToggle;
}

void CChatWindow::AddChatMessage(char *szMessage, char *szPlayerName)
{
	// Reformate the text
	char szText[MAX_NAME_LENGTH + MAX_MESSAGE_LENGTH];
	sprintf(szText, "#0000ff%s#ffffff: %s\n", szPlayerName, szMessage);
	// Add the text to the console
	m_pChatBox->AddText(szText);
}
