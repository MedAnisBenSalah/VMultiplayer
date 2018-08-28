/* =========================================================
       V:Multiplayer - http://www.vmultiplayer.com

-- File: GUIElement.h
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#ifndef GUIELEMENT_H
#define GUIELEMENT_H

enum eGUIElementType
{
	GUI_ELEMENT_TYPE_WINDOW,
	GUI_ELEMENT_TYPE_TEXT,
	GUI_ELEMENT_TYPE_EDITBOX,
	GUI_ELEMENT_TYPE_BUTTON
};

enum eGUIInput
{
	GUI_INPUT_KEYDOWN,
	GUI_INPUT_KEYUP,
	GUI_INPUT_MOUSE_LEFT_DOWN,
	GUI_INPUT_MOUSE_LEFT_UP,
	GUI_INPUT_MOUSE_RIGHT_DOWN,
	GUI_INPUT_MOUSE_RIGHT_UP,
	GUI_INPUT_MOUSE_WHEEL_DOWN,
	GUI_INPUT_MOUSE_WHEEL_UP
};

class CGUIElement
{
public:
	CGUIElement(void *pElement, eGUIElementType type);
	~CGUIElement();

	virtual eGUIElementType		GetType() { return m_type; };
	virtual bool				IsVisible();
	virtual void				SetVisible(bool bVisible);
	virtual bool				IsEnabled();
	virtual void				SetEnabled(bool bEnabled);
	virtual void				SetFocus(bool bToggle);
	virtual bool				IsFocus();
	virtual void				SetPosition(CVector2 vecPosition);
	virtual CVector2			GetPosition();
	virtual void				SetSize(CVector2 vecSize);
	virtual CVector2			GetSize();
	virtual void				SetText(char *szText);
	virtual void				GetText(char *szText);
	virtual void				SetColour(CGUIRGBA rgbaColour);
	virtual void				SetTextColour(CGUIRGBA rgbaColour);
	virtual void				SetAlpha(float fValue);
	virtual float				GetAlpha();

	template <typename T>
	T		*GetElement() { return reinterpret_cast<T *>(m_pElement); };

private:
	eGUIElementType			m_type;
	void					*m_pElement;
};

#endif