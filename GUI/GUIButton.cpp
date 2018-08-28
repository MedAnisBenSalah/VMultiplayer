/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GUIButton.cpp
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace MyGUI;

CGUIButton::CGUIButton(MyGUI::Button *pButton) : CGUIElement(pButton, GUI_ELEMENT_TYPE_BUTTON)
{
	m_pfnPressedCallbackStatic = NULL;
	m_pfnPressedCallback = NULL;
	m_pObject = NULL;
}

CGUIButton::~CGUIButton()
{

}

void CGUIButton::RegisterCallback(ButtonPressed_t pfnPressedCallback, void *pObject = NULL)
{
	// Save the button callback
	if (!pObject)
		m_pfnPressedCallbackStatic = (ButtonPressedStatic_t)pfnPressedCallback;
	else
	{
		m_pObject = pObject;
		m_pfnPressedCallback = pfnPressedCallback;
	}
	// Register the function delegate
	GetElement<Button>()->eventMouseButtonClick += newDelegate(this, &CGUIButton::HandleButtonPressed);
}

void CGUIButton::HandleButtonPressed(MyGUI::Widget *pWidget)
{
	// Call the registred callback
	if (m_pObject)
		m_pfnPressedCallback(m_pObject);
	else
		m_pfnPressedCallbackStatic();
}
