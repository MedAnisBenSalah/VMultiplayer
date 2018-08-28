/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Common.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#ifndef COMMON_H
#define COMMON_H

// General defintions
#define NAME "V:Multiplayer"
#define VERSION "0.1a Alpha 1"
#define WEBSITE "http://www.vmultiplayer.com"
#ifdef VMULTIPLAYER_CLIENT
#	define CLIENT_SETTINGS_FILE "Settings.xml"
#	define GAME_EXECUTABLE "GTAVLauncher.exe"
#	define VMULTIPLAYER_LAUNCH_HELPER_LIBRARY "VMultiplayerLaunchHelper.dll"
#	define VMULTIPLAYER_LIBRARY "VMultiplayer.dll"
#	define VMULTIPLAYER_GUI_LIBRARY "VMultiplayerGUI.dll"
#else
#	define VMULTIPLAYER_LIBRARY "VMultiplayerServer.exe"
#endif
#ifdef _WIN32
#	define VMULTIPLAYER_NETWORK_LIBRARY_x32 "VMultiplayerNetwork_x32.dll"
#	define VMULTIPLAYER_NETWORK_LIBRARY_x64 "VMultiplayerNetwork_x64.dll"
#else
#	define VMULTIPLAYER_NETWORK_LIBRARY_x32 "VMultiplayerNetwork_x32.so"
#endif

// Limits
#define MAX_PLAYERS				16
#define MAX_NAME_LENGTH			32
#define MAX_MESSAGE_LENGTH		128

// Macros
#ifdef VMULTIPLAYER_CLIENT
#	define VMULTIPLAYER_DEBUG
#	ifdef VMULTIPLAYER_DEBUG
#		define LOG(buffer, ...) CLogger::Write(buffer, __VA_ARGS__); CLogger::Flush()
#	else
#		define LOG(buffer, ...)
#	endif
#else
#	define LOG(buffer, ...) CLogger::Write(buffer, __VA_ARGS__); CLogger::Flush()
#endif

#define SAFE_DELETE(ptr) if(ptr) { delete ptr; ptr = NULL; }

// Enumerations
enum ePlayerState
{
	PLAYER_STATE_CONNECTED,
	PLAYER_STATE_ONFOOT,
	PLAYER_STATE_INVEHICLE,
	PLAYER_STATE_ENTERING_VEHICLE,
	PLAYER_STATE_EXITING_VEHICLE,
	PLAYER_STATE_DEAD,
	PLAYER_STATE_DISCONNECTED
};

#endif