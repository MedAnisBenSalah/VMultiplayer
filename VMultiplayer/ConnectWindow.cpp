/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: ConnectWindow.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CConnectWindow::CConnectWindow(CGUI *pGUI)
{
	// Reset pointers
	m_pMainWindow = NULL;
	m_pText = NULL;
	// Reset flags
	m_bInitialized = false;
	// Set the GUI pointer
	m_pGUI = pGUI;
}

CConnectWindow::~CConnectWindow()
{

}

bool CConnectWindow::Initialize(int iWidth, int iHeight)
{
	LOG("CConnectWindow::Initialize(0x%x)", m_pGUI);
	if (m_bInitialized)
		return true;

	// Load the layout
	if (!m_pGUI->LoadLayout(CONNECTWINDOW_LAYOUT))
		return false;

	// Find the main window
	m_pMainWindow = m_pGUI->FindGUIElement<CGUIWindow>(GUI_ELEMENT_TYPE_WINDOW, "ConnectWindow_MainWindow");
	m_pText = m_pGUI->FindGUIElement<CGUIText>(GUI_ELEMENT_TYPE_TEXT, "ConnectWindow_Text");
	// Validate pointers
	if (!m_pMainWindow || !m_pText)
		return false;

	// Get the window size
	CVector2 vecSize = m_pMainWindow->GetSize();
	// Set the chatwindow coordinates
	m_pMainWindow->SetPosition(CVector2((float)(iWidth / 2) - (vecSize.fX / 2), (float)(iHeight / 2) - (vecSize.fY / 2)));
	//m_pMainWindow->SetSize(CVector2((float)(iWidth / 4), (float)(iHeight / 3)));
	// Mark as initialized
	m_bInitialized = true;
	LOG("CConnectWindow::Initialize Done");
	return true;
}

void CConnectWindow::Toggle(bool bToggle)
{
	m_pMainWindow->SetVisible(bToggle);
}

bool CConnectWindow::IsVisible()
{
	return m_pMainWindow->IsVisible();
}

void CConnectWindow::SetText(char *szText, ...)
{
	// Create the arguments list
	va_list vArgs;
	va_start(vArgs, szText);
	// Create a text buffer
	char szBuffer[256];
	vsprintf(szBuffer, szText, vArgs);
	// Set the text
	if (m_pText)
		m_pText->SetText(szBuffer);

	// End the arguments list
	va_end(vArgs);
}