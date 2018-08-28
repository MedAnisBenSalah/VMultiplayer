/* =========================================================
        V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.h
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#define VMULTIPLAYER_CLIENT
// Logger
#include <Logger.h>
// Common
#include <Common.h>
// DirectX
#include <d3d11.h>
// MyGUI
#include <MyGUI.h>
#include <MyGUI_DirectX11Platform.h>
// SharedUtility
#include <SharedUtility.h>
#include <Vector2.h>
#include <RGB.h>
#include <RGBA.h>
// GUI
#include "GUIElement.h"
#include "GUIWindow.h"
#include "GUIText.h"
#include "GUIEditBox.h"
#include "GUIButton.h"
#include "GUI.h"

#define LOG_FILE "GUI_Log.txt"

#define EXPORT extern "C" __declspec( dllexport )