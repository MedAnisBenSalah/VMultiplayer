/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GUIElement.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef GUIELEMENT_H
#define GUIELEMENT_H

class CGUIElement
{
public:
	virtual eGUIElementType		GetType() = 0;
	virtual bool				IsVisible() = 0;
	virtual void				SetVisible(bool bVisible) = 0;
	virtual bool				IsEnabled() = 0;
	virtual void				SetEnabled(bool bEnabled) = 0;
	virtual void				SetFocus(bool bToggle) = 0;
	virtual bool				IsFocus() = 0;
	virtual void				SetPosition(CVector2 vecPosition) = 0;
	virtual CVector2			GetPosition() = 0;
	virtual void				SetSize(CVector2 vecSize) = 0;
	virtual CVector2			GetSize() = 0;
	virtual void				SetText(char *szText) = 0;
	virtual void				GetText(char *szText) = 0;
	virtual void				SetColour(CGUIRGBA rgbaColour) = 0;
	virtual void				SetTextColour(CGUIRGBA rgbaColour) = 0;
	virtual void				SetAlpha(float fValue) = 0;
	virtual float				GetAlpha() = 0;

};

#endif