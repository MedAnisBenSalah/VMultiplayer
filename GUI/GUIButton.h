/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GUIButton.h
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#ifndef GUIBUTTON_H
#define GUIBUTTON_H

// Callback defition
typedef void(*ButtonPressedStatic_t)();
typedef void(__cdecl *ButtonPressed_t)(void *pButton);

class CGUIButton : public CGUIElement
{
public:
	CGUIButton(MyGUI::Button *pButton);
	~CGUIButton();

	virtual void	RegisterCallback(ButtonPressed_t pfnPressedCallback, void *pObject);

protected:
	void	HandleButtonPressed(MyGUI::Widget *pWidget);

private:
	ButtonPressedStatic_t		m_pfnPressedCallbackStatic;
	ButtonPressed_t				m_pfnPressedCallback;
	void						*m_pObject;
};

#endif