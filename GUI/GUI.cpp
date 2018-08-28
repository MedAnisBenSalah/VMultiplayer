/* =========================================================
       V:Multiplayer - http://www.vmultiplayer.com

-- File: GUI.cpp
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace MyGUI;

CGUI::CGUI(ID3D11Device *pDevice)
{
	// Save the device
	m_pDevice = pDevice;
	// Reset pointers
	m_pSystem = NULL;
	m_pRenderPlatform = NULL;
	// Reset flags
	m_bInitialized = false;
	// Reset mouve vector
	m_vecMousePosition = CVector2(0.0f, 0.0f);
}

CGUI::~CGUI()
{

}

bool CGUI::Initialize(int iWidth, int iHeight, char (*pSkinsArray)[128], int iSkinsCount)
{
	LOG("CGUI::Initialize");
	if (m_bInitialized)
		return true;

	// Get the full path
	char szPath[MAX_PATH];
	CSharedUtility::GetCurrentLibraryPath(VMULTIPLAYER_GUI_LIBRARY, szPath);
	strcat(szPath, "\\MyGUI");
	// Create the render platform
	m_pRenderPlatform = new DirectX11Platform();
	m_pRenderPlatform->initialise(m_pDevice);
	// Setup the resources path
	m_pRenderPlatform->getDataManagerPtr()->addResourceLocation(szPath, false);
	// Setup layouts path
	char szLayoutsPath[MAX_PATH];
	sprintf(szLayoutsPath, "%s\\Layouts", szPath);
	m_pRenderPlatform->getDataManagerPtr()->addResourceLocation(szLayoutsPath, false);
	// Setup skins path
	char szSkinPath[MAX_PATH];
	for (int i = 0; i < iSkinsCount; i++)
	{
		sprintf(szSkinPath, "%s\\Skins\\%s", szPath, pSkinsArray[i]);
		m_pRenderPlatform->getDataManagerPtr()->addResourceLocation(szSkinPath, false);
	}
	// Setup the screen size
	m_pRenderPlatform->getRenderManagerPtr()->setViewSize(iWidth, iHeight);
	// Create the GUI system
	m_pSystem = new Gui();
	m_pSystem->initialise();
	// Mark as initialized
	m_bInitialized = true;
	
	LOG("CGUI::Initialize Done");
	return true;
}

void CGUI::Destroy()
{
	if (!m_bInitialized)
		return;

	// Destroy the system
	m_pSystem->shutdown();
	SAFE_DELETE(m_pSystem);
	// Destroy the render platform
	m_pRenderPlatform->shutdown();
	SAFE_DELETE(m_pRenderPlatform);
}

void CGUI::Render()
{
	if (!m_bInitialized)
		return;

	// Render GUI
	m_pRenderPlatform->getRenderManagerPtr()->drawOneFrame();
}

bool CGUI::SetSkin(char *szSkinName)
{
	// Generate the skin file name
	char szSkinFileName[MAX_PATH];
	sprintf(szSkinFileName, "MyGUI_%sTheme.xml", szSkinName);
	// Load the skin
	return MyGUI::ResourceManager::getInstance().load(szSkinFileName);
}

void CGUI::ToggleCursor(bool bToggle)
{
	// Toggle the GUI cursor
	if (m_bInitialized)
		PointerManager::getInstance().setVisible(bToggle);
}

bool CGUI::IsCursorVisible()
{
	// Toggle the GUI cursor
	if (m_bInitialized)
		return PointerManager::getInstance().isVisible();
	else
		return false;
}

bool CGUI::LoadLayout(char *szLayoutName)
{
	// Load the layout
	VectorWidgetPtr pvecWidget = LayoutManager::getInstance().loadLayout(szLayoutName);
	if (pvecWidget.empty())
		return false;
	else
		return true;
}

void CGUI::HandleInput(eGUIInput input, DWORD dwKey)
{
	switch (input)
	{
	case GUI_INPUT_KEYDOWN:
		InputManager::getInstance().injectKeyPress(VirtualKeyToKeyCode(dwKey), 0);
		break;

	case GUI_INPUT_KEYUP:
		InputManager::getInstance().injectKeyRelease(VirtualKeyToKeyCode(dwKey));
		break;

	case GUI_INPUT_MOUSE_RIGHT_DOWN:
		InputManager::getInstance().injectMousePress((int)m_vecMousePosition.fX, (int)m_vecMousePosition.fY, MouseButton::Right);
		break;

	case GUI_INPUT_MOUSE_RIGHT_UP:
		InputManager::getInstance().injectMouseRelease((int)m_vecMousePosition.fX, (int)m_vecMousePosition.fY, MouseButton::Right);
		break;

	case GUI_INPUT_MOUSE_LEFT_DOWN:
		InputManager::getInstance().injectMousePress((int)m_vecMousePosition.fX, (int)m_vecMousePosition.fY, MouseButton::Left);
		break;

	case GUI_INPUT_MOUSE_LEFT_UP:
		InputManager::getInstance().injectMouseRelease((int)m_vecMousePosition.fX, (int)m_vecMousePosition.fY, MouseButton::Left);
		break;

	case GUI_INPUT_MOUSE_WHEEL_DOWN:
		InputManager::getInstance().injectMousePress((int)m_vecMousePosition.fX, (int)m_vecMousePosition.fY, MouseButton::Middle);
		break;

	case GUI_INPUT_MOUSE_WHEEL_UP:
		InputManager::getInstance().injectMouseRelease((int)m_vecMousePosition.fX, (int)m_vecMousePosition.fY, MouseButton::Middle);
		break;
	}
}

void CGUI::HandleTextInput(char cInput)
{
	// Handle backspace
	if (cInput == VK_BACK)
		InputManager::getInstance().injectKeyPress(KeyCode::Backspace, 0);
	else
		InputManager::getInstance().injectKeyPress(KeyCode::None, (Char)cInput);
}

void CGUI::HandleMouseMove(CVector2 vecPosition)
{
	// Handle mouse mouvement only if the mouse is enabled
	if (!IsCursorVisible())
		return;

	// Save the new mouve position
	m_vecMousePosition = vecPosition;
	// Set the mouse position
	MyGUI::InputManager::getInstance().injectMouseMove((int)m_vecMousePosition.fX, (int)m_vecMousePosition.fY, 0);
}

void CGUI::HandleMouseWheelMove(float fValue)
{
	// Handle mouse mouvement only if the mouse is enabled
	if (!IsCursorVisible())
		return;

	// Set the mouse position
	MyGUI::InputManager::getInstance().injectMouseMove((int)m_vecMousePosition.fX, (int)m_vecMousePosition.fY, (int)fValue);
}

CGUIElement *CGUI::CreateElement(eGUIElementType type, CVector2 vecPosition, CVector2 vecSize)
{
	LOG("CGUI::CreateElement(%d, (%f, %f), (%f, %f)", type, vecPosition.fX, vecPosition.fY, vecSize.fX, vecSize.fY);
	// Create our GUI element
	switch (type)
	{
	// Simple Text
	case GUI_ELEMENT_TYPE_TEXT:
	{
		TextBox *pElement = m_pSystem->createWidget<TextBox>("TextBox", (int)vecPosition.fX, (int)vecPosition.fY, (int)vecSize.fX, (int)vecSize.fY,
			MyGUI::Align::Default, "Main");

		pElement->setTextShadow(true);
		return new CGUIText(pElement);
	}
	/*case GUI_ELEMENT_TYPE_EDITBOX:
		return new CGUIText(pElement);*/
	}
	return NULL;
}

CGUIElement *CGUI::FindElement(eGUIElementType type, char *szWidgetName)
{
	// Find the element
	Widget *pElement = m_pSystem->findWidget<Widget>(szWidgetName);
	if (!pElement)
		return NULL;

	// Create a GUI instance accordingly
	switch (type)
	{
		// Window
		case GUI_ELEMENT_TYPE_WINDOW:
			return new CGUIWindow(pElement->castType<Window>());

		// Simple Text
		case GUI_ELEMENT_TYPE_TEXT:
			return new CGUIText(pElement->castType<TextBox>());

		// EditBox
		case GUI_ELEMENT_TYPE_EDITBOX:
			return new CGUIEditBox(pElement->castType<EditBox>());

		// Button
		case GUI_ELEMENT_TYPE_BUTTON:
			return new CGUIButton(pElement->castType<Button>());
	}
	return NULL;
}

MyGUI::KeyCode	CGUI::VirtualKeyToKeyCode(DWORD dwVKKey)
{
	// Handle F* keys
	if (dwVKKey >= VK_F1 && dwVKKey <= VK_F10)
		return (KeyCode::Enum)(dwVKKey - 53);

	// Handle numbers
	if (dwVKKey >= '0' && dwVKKey <= '9')
		return dwVKKey == '0' ? KeyCode::Zero : (KeyCode::Enum)(dwVKKey - 47);

	// Other keys
	switch (dwVKKey)
	{
	case VK_BACK:
		return KeyCode::Backspace;

	case VK_RETURN:
		return KeyCode::Return;

	case VK_ESCAPE:
		return KeyCode::Escape;

	case VK_TAB:
		return KeyCode::Tab;

	case VK_CAPITAL:
		return KeyCode::Capital;

	case VK_LSHIFT:
		return KeyCode::LeftShift;

	case VK_RSHIFT:
		return KeyCode::RightShift;

	case VK_LCONTROL:
		return KeyCode::LeftControl;

	case VK_RCONTROL:
		return KeyCode::RightControl;

	case VK_LMENU:
		return KeyCode::LeftAlt;

	case VK_RMENU:
		return KeyCode::RightAlt;
	}

	return KeyCode::None;
}