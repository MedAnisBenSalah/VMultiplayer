/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: WindowHook.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef WINDOWHOOK_H
#define WINDOWHOOK_H

class CWindowHook
{
public:
	static void Install();
	static LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static WNDPROC		m_pfnOldProc;


};

#endif