/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GUIText.cpp
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace MyGUI;

CGUIEditBox::CGUIEditBox(MyGUI::EditBox *pEditBox) : CGUIElement(pEditBox, GUI_ELEMENT_TYPE_EDITBOX)
{

}

CGUIEditBox::~CGUIEditBox()
{

}

void CGUIEditBox::AddText(char *szText)
{
	if (!GetElement<Widget>())
		return;

	GetElement<EditBox>()->addText(szText);
}
