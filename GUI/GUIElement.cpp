/* =========================================================
      V:Multiplayer - http://www.vmultiplayer.com

-- File: GUIElement.cpp
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace MyGUI;

CGUIElement::CGUIElement(void *pElement, eGUIElementType type)
{
	// Save the type
	m_type = type;
	// Save the pointer
	m_pElement = pElement;
}

CGUIElement::~CGUIElement()
{

}

void CGUIElement::SetVisible(bool bVisible)
{
	if (GetElement<Widget>())
		return GetElement<Widget>()->setVisible(bVisible);
}

bool CGUIElement::IsVisible()
{
	if (!GetElement<Widget>())
		return false;
	else
		return GetElement<Widget>()->getVisible();
}

void CGUIElement::SetEnabled(bool bEnabled)
{
	if (GetElement<Widget>())
		return GetElement<Widget>()->setEnabled(bEnabled);
}

bool CGUIElement::IsEnabled()
{
	if (!GetElement<Widget>())
		return false;
	else
		return GetElement<Widget>()->getEnabled();
}

void CGUIElement::SetFocus(bool bToggle)
{
	if (GetElement<Widget>())
		bToggle ? MyGUI::InputManager::getInstance().setKeyFocusWidget(GetElement<Widget>()) : 
			MyGUI::InputManager::getInstance().resetKeyFocusWidget();
}

bool CGUIElement::IsFocus()
{
	if (GetElement<Widget>())
		return MyGUI::InputManager::getInstance().getKeyFocusWidget() == GetElement<Widget>();
	else
		return false;
}

void CGUIElement::SetPosition(CVector2 vecPosition)
{
	if (!GetElement<Widget>())
		return;

	GetElement<Widget>()->setPosition((int)vecPosition.fX, (int)vecPosition.fY);
}

CVector2 CGUIElement::GetPosition()
{
	if (!GetElement<Widget>())
		return CVector2();

	IntPoint point = GetElement<Widget>()->getPosition();
	return CVector2((float)point.left, (float)point.top);
}

void CGUIElement::SetSize(CVector2 vecPosition)
{
	if (!GetElement<Widget>())
		return;

	GetElement<Widget>()->setSize((int)vecPosition.fX, (int)vecPosition.fY);
}

CVector2 CGUIElement::GetSize()
{
	if (!GetElement<Widget>())
		return CVector2();

	IntSize size = GetElement<Widget>()->getSize();
	return CVector2((float)size.width, (float)size.height);
}

void CGUIElement::SetText(char *szText)
{
	if (!GetElement<Widget>())
		return;

	GetElement<TextBox>()->setCaption(szText);
}

void CGUIElement::GetText(char *szText)
{
	strcpy(szText, "Invalid element");
	if (!GetElement<Widget>())
		return;

	// Get element string
	UString strText = GetElement<TextBox>()->getCaption();
	// Copy it to the output buffer
	for (int i = 0; i < strText.length(); i++)
		szText[i] = strText[i];

	// End of string
	szText[strText.length()] = 0;
}

void CGUIElement::SetColour(CGUIRGBA rgbaColour)
{
	if (!GetElement<Widget>())
		return;

	GetElement<Widget>()->setColour(Colour(rgbaColour.fRed, rgbaColour.fGreen, rgbaColour.fBlue, rgbaColour.fAlpha));
}

void CGUIElement::SetTextColour(CGUIRGBA rgbaColour)
{
	if (!GetElement<Widget>())
		return;

	GetElement<TextBox>()->setTextColour(Colour(rgbaColour.fRed, rgbaColour.fGreen, rgbaColour.fBlue, rgbaColour.fAlpha));
}

void CGUIElement::SetAlpha(float fValue)
{
	if (!GetElement<Widget>())
		return;

	GetElement<Widget>()->setAlpha(fValue);
}

float CGUIElement::GetAlpha()
{
	if (!GetElement<Widget>())
		return 0.0f;

	return GetElement<Widget>()->getAlpha();
}
