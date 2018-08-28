/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GUICommon.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef GUICOMMON_H
#define GUICOMMON_H

// General definitions
#define GUI_SKINS_COUNT	3
#define CHATWINDOW_LAYOUT "VMultiplayer_ChatWindow.layout"
#define CONNECTWINDOW_LAYOUT "VMultiplayer_ConnectWindow.layout"

// Arrays
static char szSkinsArray[GUI_SKINS_COUNT][128] = { "BlackBlue", "BlackOrange", "BlueWhite" };

// Enumerations
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

#endif