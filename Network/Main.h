/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

// RakNet
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>

#ifdef _WIN32
#	include <Windows.h>
#	pragma comment(lib, "ws2_32.lib")
#endif
#include <stdio.h>
#include <math.h>
// Logger
#include <Logger.h>
// Common
#include <Common.h>
// SharedUtility
#include <SharedUtility.h>
#include <Vector2.h>
// Network
#include "NetSenderInfo.h"
#include "NetMessage.h"
#include "RFParameters.h"
#include "RemoteFunction.h"
#include "RFManager.h"
#include "Network.h"

#define LOG_FILE "Network_Log.txt"

#define EXPORT extern "C" __declspec( dllexport )