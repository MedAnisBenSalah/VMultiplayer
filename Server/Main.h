/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.h
-- Project: Server
-- Author(s): OrMisicL

=============================================================*/

#ifdef _WIN32
#	include <Windows.h>
#	include <Winternl.h>
#endif
#include <stdio.h>
#include <math.h>

// Common
#include <Common.h>
// SharedUtility
#include <SharedUtility.h>
#include <Library.h>
#include <Vector3.h>
// Component
#include <Component.h>
// Logger
#include <Logger.h>
// Managers
#include <ManagerBase.h>
// Network
#include <MessageIdentifiers.h>
#include <RFIdentifiers.h>
#include <BitStream.h>
#include <NetSenderInfo.h>
#include <NetMessage.h>
#include <RFParameters.h>
#include <NetCommon.h>
#include <Network.h>
// RFS
#include "MainRFS.h"
#include "PlayerRFS.h"
// Network 
#include "NetworkPlayer.h"
// Managers
#include "PlayerManager.h"
// Server
#include "Server.h"

// General server defitions
#define LOG_FILE	"ServerLog.txt"

void LogPrintf(char *szBuffer, ...);