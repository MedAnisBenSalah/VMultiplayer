/* =========================================================
         V:Multiplayer - http://www.vmultiplayer.com

-- File: GUI.h
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#ifndef GUI_H
#define GUI_H

class CGUI
{
public:
	CGUI(ID3D11Device *pDevice);
	~CGUI();

	virtual bool Initialize(int iWidth, int iHeight, char (*pSkinsArray)[128], int iSkinsCount);
	virtual void Destroy();
	virtual void ToggleCursor(bool bToggle);
	virtual bool IsCursorVisible();
	virtual bool SetSkin(char *szSkinName);
	virtual void Render();
	virtual void HandleInput(eGUIInput input, DWORD dwKey);
	virtual void HandleTextInput(char cInput);
	virtual void HandleMouseMove(CVector2 vecPosition);
	virtual void HandleMouseWheelMove(float fValue);

	virtual bool LoadLayout(char *szLayoutName);
	virtual CGUIElement *CreateElement(eGUIElementType type, CVector2 vecPosition, CVector2 vecSize);
	virtual CGUIElement *FindElement(eGUIElementType type, char *szWidgetName);

protected:
	MyGUI::KeyCode	VirtualKeyToKeyCode(DWORD dwVKKey);

private:
	ID3D11Device					*m_pDevice;
	bool							m_bInitialized;
	MyGUI::Gui						*m_pSystem;
	MyGUI::DirectX11Platform		*m_pRenderPlatform;
	CVector2						m_vecMousePosition;

};

#endif