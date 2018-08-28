/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GameHooks.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef GAMEHOOKS_H
#define GAMEHOOKS_H

DWORD64 Disable(DWORD64 ctx);

class CGameHooks
{
public:
	static void Install();
};

#endif