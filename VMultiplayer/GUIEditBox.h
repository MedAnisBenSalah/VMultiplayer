/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GUIEditBox.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef GUIEDITBOX_H
#define GUIEDITBOX_H

class CGUIEditBox : public CGUIElement
{
public:
	virtual void AddText(char *szText) = 0;

};

#endif