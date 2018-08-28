/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include <Windows.h>
#include <Winternl.h>
#include <stdio.h>
#include <math.h>
// DirectX
#define DIRECTINPUT_VERSION DIRECTINPUT_HEADER_VERSION // No more "Defaulting to version xxxx" warning
#include <d3d11.h>
#include <dinput.h>
// Assembly
#include "Assembly.h"
// Utility
#include "Utility.h"
// SharedUtility
#include <SharedUtility.h>
#include <Library.h>
#include <Thread.h>
#include <Vector2.h>
#include <Vector3.h>
#include <RGB.h>
#include <RGBA.h>
// ExceptionHandler
#include <ExceptionHandler.h>
// Common
#include <Common.h>
// Component
#include <Component.h>
// MinHook
#include <MinHook.h>
// Logger
#include <Logger.h>
// Shared Managers
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
// Direct3D11 Hooks
#include "Direct3D11DeviceHook.h"
#include "IDXGISwapChainHook.h"
// DirectInput Hook
#include "DirectInput8Hook.h"
#include "DirectInput8DeviceHook.h"
// GUI
#include "GUI.h"
// Core
#include "Component.h"
// Graphics
#include "ChatWindow.h"
#include "ConnectWindow.h"
#include "Graphics.h"
// VObjects
#include "VObjectBase.h"
#include "VScriptVector3.h"
#include "VModelInfo.h"
#include "VModel.h"
#include "VPlayerInfo.h"
#include "VEntity.h"
#include "VDynamicEntity.h"
#include "VPhysical.h"
#include "VPed.h"
#include "VPedFactory.h"
#include "VThread.h"
#include "VThreadManager.h"
// VPools
#include "VPool.h"
#include "VPlayerInfoPool.h"
#include "VPedPool.h"
#include "VPools.h"
// VGame
#include "VStreaming.h"
#include "VGame.h"
// Hooks
#include "Hooks.h"
#include "WindowHook.h"
// Game
#include "Model.h"
// Multiplayer
#include "NetworkPlayer.h"
// Network
#include "MainRFS.h"
#include "PlayerRFS.h"
#include "Client.h"
// Game
#include "Address.h"
#include "Patches.h"
#include "GameHooks.h"
#include "LocalPlayer.h"
#include "Game.h"
// Managers
#include "PlayerManager.h"
// Multiplayer
#include "Multiplayer.h"
// Core
#include "Core.h"

// General client defitions
#define LOG_FILE	"Log.txt"
