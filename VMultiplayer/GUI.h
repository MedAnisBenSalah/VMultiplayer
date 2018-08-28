/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: GUI.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef GUI_H
#define GUI_H

// Include all GUI files
#include "GUICommon.h"
#include "GUIElement.h"
#include "GUIWindow.h"
#include "GUIText.h"
#include "GUIEditBox.h"
#include "GUIButton.h"

class CGUI
{
public:
	virtual bool Initialize(int iWidth, int iHeight, char (*pSkinsArray)[128], int iSkinsCount) = 0;
	virtual void Destroy() = 0;
	virtual void ToggleCursor(bool bToggle) = 0;
	virtual bool IsCursorVisible() = 0;
	virtual bool SetSkin(char *szSkinName) = 0;
	virtual void Render() = 0;
	virtual void HandleInput(eGUIInput input, DWORD dwKey) = 0;
	virtual void HandleTextInput(char cInput) = 0;
	virtual void HandleMouseMove(CVector2 vecPosition) = 0;
	virtual void HandleMouseWheelMove(float fValue) = 0;

	virtual bool LoadLayout(char *szLayoutName) = 0;
	virtual CGUIElement *CreateElement(eGUIElementType type, CVector2 vecPosition, CVector2 vecSize) = 0;
	virtual CGUIElement *FindElement(eGUIElementType type, char *szWidgetName) = 0;

	// Casting functions for creating/finding widgets
	template <typename T>
	T *CreateGUIElement(eGUIElementType type, CVector2 vecPosition, CVector2 vecSize)
	{
		return reinterpret_cast<T *>(CreateElement(type, vecPosition, vecSize));
	};

	template <typename T>
	T *FindGUIElement(eGUIElementType type, char *szWidgetName)
	{
		return reinterpret_cast<T *>(FindElement(type, szWidgetName));
	};
};

#endif