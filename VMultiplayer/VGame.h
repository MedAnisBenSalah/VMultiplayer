/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VGame.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VGAMEPLAY_H
#define VGAMEPLAY_H

enum eVSceenFadeType
{
	VSCREEN_FADE_TYPE_OUT,
	VSCREEN_FADE_TYPE_IN
};

enum eVGameState
{
	VGAME_STATE_UNINITIALIZED = -1,
	VGAME_STATE_PLAYING,
	VGAME_STATE_INTRO_MOVIES,
	VGAME_STATE_2,
	VGAME_STATE_LEGAL_SCREEN,
	VGAME_STATE_4,
	VGAME_STATE_5,
	VGAME_STATE_LOADING_SCREEN
};

class CVGame
{
public:
	static DWORD		GetKeyHash(char *szKey);
	static void			ShutdownLoadingScreen();
	static void			FadeScreen(eVSceenFadeType type, int iDuration);
	static void			Wait(float fTime, VGtaThread *pThread);
	static eVGameState	GetGameState();
	static void			SetGameState(eVGameState state);

	template <typename T>
	static T *GtaAllocate(DWORD dwSize)
	{
		// Call the gtaAllocate
		return reinterpret_cast<T *>(CAddress::FUNC_GtaAllocate(dwSize));
	};

private:

};

#endif