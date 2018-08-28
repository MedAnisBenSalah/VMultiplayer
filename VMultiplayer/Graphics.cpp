/* =========================================================
         V:Multiplayer - http://www.vmultiplayer.com

-- File: Graphics.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"
#include <Windowsx.h>

// Exported functions from GUI library
typedef CGUI *(WINAPI *VMultiplayer_CreateGUI_t)(ID3D11Device *pDevice);
VMultiplayer_CreateGUI_t		pfnVMultiplayer_CreateGUI = NULL;

CGraphics::CGraphics(CComponent *pComponent)
{
	// Set the component
	m_pComponent = pComponent;
	// Reset pointers
	m_pGUI = NULL;
	m_pVersionText = NULL;
	m_pChatWindow = NULL;
	m_pConnectWindow = NULL;
	// Reset flag
	m_bInitialized = false;
}

CGraphics::~CGraphics()
{

}

bool CGraphics::Initialize(int iWidth, int iHeight, ID3D11Device *pDevice)
{
	LOG("CGraphics::Initialize(0x%x)", pDevice);
	if (m_bInitialized)
		return true;

	// Get the initializing funtion address
	pfnVMultiplayer_CreateGUI = m_pComponent->GetInitializeAddress<VMultiplayer_CreateGUI_t>();
	// Create the GUI instance
	m_pGUI = pfnVMultiplayer_CreateGUI(pDevice);
	// Try to initialize the network
	if (!m_pGUI->Initialize(iWidth, iHeight, szSkinsArray, GUI_SKINS_COUNT))
		return false;

	// Set the GUI skin
	m_pGUI->SetSkin(szSkinsArray[0]);
	// Hide the cursor
	m_pGUI->ToggleCursor(false);
	// Create the version text
	m_pVersionText = m_pGUI->CreateGUIElement<CGUIText>(GUI_ELEMENT_TYPE_TEXT, CVector2(10.0f, (float)(iHeight - 25.0f)), CVector2(500.0f, 200.0f));
	m_pVersionText->SetText(NAME " v" VERSION " - Build " __DATE__);
	m_pVersionText->SetTextColour(CGUIRGBA(1.0f, 1.0f, 1.0f, 1.0f));
	// Create the chatwindow
	m_pChatWindow = new CChatWindow(m_pGUI);
	if (!m_pChatWindow || !m_pChatWindow->Initialize(iWidth, iHeight))
		return false;

	// Hide the chatwindow
	m_pChatWindow->Toggle(false);
	// Create the connectwindow
	m_pConnectWindow = new CConnectWindow(m_pGUI);
	if (!m_pConnectWindow || !m_pConnectWindow->Initialize(iWidth, iHeight))
		return false;

	// Hide it
	m_pConnectWindow->Toggle(false);
	// Mark as initialized
	m_bInitialized = true;

	LOG("CGraphics::Initialize Done");
	return true;
}

void CGraphics::DoGameLoad()
{
	// Display the chatwindow
	//m_pChatWindow->Toggle(true);
	// Display the connect window
	m_pConnectWindow->Toggle(true);
}

void CGraphics::HandleInput(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Handle every message type
	switch (uMsg)
	{
	case WM_KEYUP:
		m_pGUI->HandleInput(GUI_INPUT_KEYUP, (DWORD)wParam);
		break;

	case WM_KEYDOWN:
		m_pGUI->HandleInput(GUI_INPUT_KEYDOWN, (DWORD)wParam);
		break;

	case WM_LBUTTONDOWN:
		m_pGUI->HandleInput(GUI_INPUT_MOUSE_LEFT_DOWN, 0);
		break;

	case WM_LBUTTONUP:
		m_pGUI->HandleInput(GUI_INPUT_MOUSE_LEFT_UP, 0);
		break;

	case WM_RBUTTONDOWN:
		m_pGUI->HandleInput(GUI_INPUT_MOUSE_RIGHT_DOWN, 0);
		break;

	case WM_RBUTTONUP:
		m_pGUI->HandleInput(GUI_INPUT_MOUSE_RIGHT_UP, 0);
		break;

	case WM_MBUTTONDOWN:
		m_pGUI->HandleInput(GUI_INPUT_MOUSE_WHEEL_DOWN, 0);
		break;

	case WM_MBUTTONUP:
		m_pGUI->HandleInput(GUI_INPUT_MOUSE_WHEEL_UP, 0);
		break;

	case WM_MOUSEMOVE:
		m_pGUI->HandleMouseMove(CVector2((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam)));
		break;

	case WM_MOUSEWHEEL:
		m_pGUI->HandleMouseWheelMove((float)HIWORD(wParam));
		break;

	case WM_CHAR:
		m_pGUI->HandleTextInput(wParam);
		break;
	}
}
