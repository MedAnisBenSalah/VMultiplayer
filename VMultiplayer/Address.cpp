/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Address.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/


#include "Main.h"

// Patterns
#define C_CPopulation__CreatePed "\x48\x8B\xC4\x48\x89\x58\x18\x4C\x89\x48\x20\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\xC1\x48\x81\xEC\xD0\x00\x00\x00"

// Callbacks
DWORD64		CAddress::CALLBACK_CPopulation__CreatePed = NULL;
DWORD64		CAddress::CALLBACK_CPopulation__CreateVehicle = NULL;
DWORD64		CAddress::CALLBACK_CPopulation__CreateParkedVehicle = NULL;
DWORD64		CAddress::CALLBACK_GtaThread__Run = NULL;
DWORD64		CAddress::CALLBACK_GetCurrentGtaThread = NULL;

// Functions
ShutdownLoadingScreen_t				CAddress::FUNC_ShutdownLoadingScreen = NULL;
FadeScreen_t						CAddress::FUNC_FadeScreen = NULL;
GetHashKey_t						CAddress::FUNC_GetHashKey = NULL;
GtaAllocate_t						CAddress::FUNC_GtaAllocate = NULL;

RequestModel_t						CAddress::FUNC_RequestModel = NULL;
HasModelLoaded_t					CAddress::FUNC_HasModelLoaded = NULL;

CStreaming__GetModelFromHash_t		CAddress::FUNC_CStreaming__GetModelFromHash = NULL;

CPlayerInfo__Constructor_t			CAddress::FUNC_CPlayerInfo__Constructor = NULL;

CPed__Constructor_t					CAddress::FUNC_CPed__Constructor = NULL;
CPed__GetID_t						CAddress::FUNC_CPed__GetID = NULL;
CPed__SetupIKManager_t				CAddress::FUNC_CPed__SetupIKManager = NULL;
CPed__SpawnAt_t						CAddress::FUNC_CPed__SpawnAt = NULL;
CPed__SetModel_t					CAddress::FUNC_CPed__SetModel = NULL;

GtaThread__Constructor_t			CAddress::FUNC_GtaThread__Constructor = NULL;

CPool__Allocate_t					CAddress::FUNC_CPool__Allocate = NULL;

// Pointers
DWORD64		CAddress::PTR_PedFactory = NULL;
DWORD64		CAddress::PTR_ThreadManager = NULL;
DWORD64		CAddress::PTR_CurrentThread = NULL;
DWORD64		CAddress::PTR_PlayerInfoPool = NULL;
DWORD64		CAddress::PTR_PedPool = NULL;

// Variables
DWORD64		CAddress::VAR_GameState = NULL;
DWORD64		CAddress::VAR_ThreadsCount = NULL;
DWORD64		CAddress::VAR_TlsIndex = NULL;

// Offsets

// NOTE: I wanted to use patterns for memory addresses here, but finding and updating patterns is much more harder than
// memory addresses, besides there are pointers which are even harder to maintain with pattern finding, so we'll stick to
// the regular memory addresses and manually update them for every release.
// Or somebody else who's not too lazy to find all the patterns and is willing to maintain them for every release :D
bool CAddress::Initialize(DWORD64 dwBaseAddress)
{
	// Verify if the module has unpacked itself
	if (!CUtility::FindPattern(C_CPopulation__CreatePed, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"))
		return false;

	// Callbacks
	CALLBACK_CPopulation__CreatePed = CUtility::FindPattern(C_CPopulation__CreatePed, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	CALLBACK_CPopulation__CreateVehicle = dwBaseAddress + 0x140A81C88;
	CALLBACK_CPopulation__CreateParkedVehicle = dwBaseAddress + 0x1409F5674;
	CALLBACK_GtaThread__Run = dwBaseAddress + 0x140FC58F8;
	CALLBACK_GetCurrentGtaThread = dwBaseAddress + 0x140FC3548;

	// Functions
	FUNC_ShutdownLoadingScreen = (ShutdownLoadingScreen_t)(dwBaseAddress + 0x13FD9B9B0);
	FUNC_FadeScreen = (FadeScreen_t)(dwBaseAddress + 0x13FE38560);
	FUNC_GetHashKey = (GetHashKey_t)(dwBaseAddress + 0x140D041F4);
	FUNC_GtaAllocate = (GtaAllocate_t)(dwBaseAddress + 0x13FBC1238);

	FUNC_RequestModel = (RequestModel_t)(dwBaseAddress + 0x14081B4B0);
	FUNC_HasModelLoaded = (HasModelLoaded_t)(dwBaseAddress + 0x140830DE8);

	FUNC_CStreaming__GetModelFromHash = (CStreaming__GetModelFromHash_t)(dwBaseAddress + 0x14105B49C);

	FUNC_CPlayerInfo__Constructor = (CPlayerInfo__Constructor_t)(dwBaseAddress + 0x1401B17BC);

	FUNC_CPed__Constructor = (CPed__Constructor_t)(dwBaseAddress + 0x1402CE9AC);
	FUNC_CPed__GetID = (CPed__GetID_t)(dwBaseAddress + 0x140FCA9D4);
	FUNC_CPed__SetupIKManager = (CPed__SetupIKManager_t)(dwBaseAddress + 0x1402FE878);
	FUNC_CPed__SpawnAt = (CPed__SpawnAt_t)(dwBaseAddress + 0x140560158);
	FUNC_CPed__SetModel = (CPed__SetModel_t)(dwBaseAddress + 0x14042B014);

	FUNC_GtaThread__Constructor = (GtaThread__Constructor_t)(dwBaseAddress + 0x14054AB00);

	FUNC_CPool__Allocate = (CPool__Allocate_t)(dwBaseAddress + 0x140FD16D4);

	// Pointers
	PTR_PedFactory = dwBaseAddress + 0x141D446C8;
	PTR_ThreadManager = dwBaseAddress + 0x1425540C0;
	PTR_CurrentThread = dwBaseAddress + 0x1425544F0;
	PTR_PlayerInfoPool = dwBaseAddress + 0x141D44980;
	PTR_PedPool = dwBaseAddress + 0x141D44690;

	// Variables
	VAR_GameState = dwBaseAddress + 0x141980294;
	VAR_ThreadsCount = dwBaseAddress + 0x1425540C8;
	VAR_TlsIndex = dwBaseAddress + 0x14264FF1C;

	return true;

}