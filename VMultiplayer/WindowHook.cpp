/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: WindowHooks.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/


#include "Main.h"

// Function prototype for RegisterClass
typedef ATOM (WINAPI *RegisterClassW_t)(WNDCLASS *pClass);
RegisterClassW_t pfn_RegisterClass;
// Function pointer
WNDPROC CWindowHook::m_pfnOldProc = NULL;

ATOM WINAPI RegisterClass_Hook(WNDCLASS *pClass)
{
	LOG("RegisterClass_Hook Started");
	// Save the old window proc
	CWindowHook::m_pfnOldProc = pClass->lpfnWndProc;
	// Change the window proc function address
	pClass->lpfnWndProc = CWindowHook::WndProc;
	LOG("RegisterClass_Hook End");
	// Resume the function
	return pfn_RegisterClass(pClass);
}

void CWindowHook::Install()
{
	// Since using the old SetWindowLongPtr hook would crash (a protection maybe?)
	// We're going to do it the dirty way !
	// Hook for RegisterClass
	pfn_RegisterClass = (RegisterClassW_t)CHooks::InstallDetoursHook((BYTE *)GetProcAddress(GetModuleHandle("User32.dll"),
		"RegisterClassW"), (PBYTE)RegisterClass_Hook);
}

LRESULT	APIENTRY CWindowHook::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// A flag to indicate whether or not we should process the GUI
	bool bProcessGUI = true;
	// Check key presses
	if (uMsg == WM_KEYUP)
	{
		// Input toggle
		if (wParam == VK_F7)
		{
			// Toggle the user input
			CCore::GetMultiplayer()->ChangeInputState();
		}
		// Escape
		else if (wParam == VK_ESCAPE && CCore::GetGraphics()->GetChatWindow()->IsInputEnabled())
		{
			// Toggle the user input off
			CCore::GetMultiplayer()->ChangeInputState();
			// Indicate that we're not going to process the GUI for this frame
			bProcessGUI = false;
		}
		// Enter
		else if (wParam == VK_RETURN && CCore::GetGraphics()->GetChatWindow()->IsInputEnabled())
		{
			// Parse the received input
			CMultiplayer::ParseInput();
			// Indicate that we're not going to process the GUI for this frame
			bProcessGUI = false;
		}
	}
	else if (uMsg == WM_KEYDOWN || uMsg == WM_CHAR)
	{
		// Never let the return press reach the text input
		if (wParam == VK_RETURN && CCore::GetGraphics()->GetChatWindow()->IsInputEnabled())
		{
			// Parse the received input
			CMultiplayer::ParseInput();
			// Indicate that we're not going to process the GUI for this frame
			bProcessGUI = false;
		}
	}
	// Backspace as char input
	if (uMsg == WM_CHAR)
	{
		// Never let the return press reach the text input
		if (wParam == VK_BACK && CCore::GetGraphics()->GetChatWindow()->IsInputEnabled())
			// Indicate that we're not going to process the GUI for this frame
			bProcessGUI = false;
	}
	// Handle the graphics input
	if (bProcessGUI && CCore::GetGraphics()->GetGUI())
		CCore::GetGraphics()->HandleInput(uMsg, wParam, lParam);

	// Call the old WndProc
	return CallWindowProc(m_pfnOldProc, hWnd, uMsg, wParam, lParam);
}