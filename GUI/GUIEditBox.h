/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GUIEditBox.h
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#ifndef GUIEDITBOX_H
#define GUIEDITBOX_H

class CGUIEditBox : public CGUIElement
{
public:
	CGUIEditBox(MyGUI::EditBox *pEditBox);
	~CGUIEditBox();

	virtual void AddText(char *szText);

private:

};

#endif