/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Address.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/


#ifndef ADDRESS_H
#define ADDRESS_H

// Functions definitions
typedef void(*FadeScreen_t)(int iTime, BYTE byteType);
typedef void(*ShutdownLoadingScreen_t)(BOOL bToggle);
typedef DWORD(*GetHashKey_t)(char *szKey, DWORD dwUnknown);
typedef DWORD64(*GtaAllocate_t)(DWORD dwSize);
typedef void(*RequestModel_t)(DWORD dwModelHash);
typedef bool(*HasModelLoaded_t)(DWORD dwModelHash);
typedef VPlayerInfo *(*CPlayerInfo__Constructor_t)(VPlayerInfo *pPlayerInfo, DWORD dwUnknown, DWORD64 dwIsNetworkSignedIn);
typedef VPed *(*CPed__Constructor_t)(VPed *pPed, DWORD dwUnknown, DWORD64 dwUnknown2, DWORD dwUknown3);
typedef DWORD(*CPed__GetID_t)(VPed *pPed);
typedef void(*CPed__SetupIKManager_t)(VPed *pPed, VModelInfo *pModelInfo);
typedef void(*CPed__SpawnAt_t)(VPed *pPed, float fX, float fY, float fZ, BYTE byteUnknown1, BYTE byteUnknown2, DWORD dwUnknown3);
typedef void(*CPed__SetModel_t)(VPed *pPed, VModelInfo *pModelInfo);
typedef VGtaThread *(*GtaThread__Constructor_t)(VGtaThread *pThread);
typedef void *(*CPool__Allocate_t)(VPool *pPool);
typedef void *(*CStreaming__GetModelFromHash_t)(DWORD dwModelHash, VModelInfo *pModelInfo);

class CAddress
{
	public:
		static bool	Initialize(DWORD64 dwBaseAddress);

		// Callbacks
		static DWORD64						CALLBACK_CPopulation__CreatePed;
		static DWORD64						CALLBACK_CPopulation__CreateVehicle;
		static DWORD64						CALLBACK_CPopulation__CreateParkedVehicle;

		static DWORD64						CALLBACK_GtaThread__Run;
		static DWORD64						CALLBACK_GetCurrentGtaThread;

		// Functions
		static ShutdownLoadingScreen_t				FUNC_ShutdownLoadingScreen;
		static FadeScreen_t							FUNC_FadeScreen;
		static GetHashKey_t							FUNC_GetHashKey;
		static GtaAllocate_t						FUNC_GtaAllocate;

		static RequestModel_t						FUNC_RequestModel;
		static HasModelLoaded_t						FUNC_HasModelLoaded;
		
		static CStreaming__GetModelFromHash_t		FUNC_CStreaming__GetModelFromHash;

		static CPlayerInfo__Constructor_t			FUNC_CPlayerInfo__Constructor;

		static CPed__Constructor_t					FUNC_CPed__Constructor;
		static CPed__GetID_t						FUNC_CPed__GetID;
		static CPed__SetupIKManager_t				FUNC_CPed__SetupIKManager;
		static CPed__SpawnAt_t						FUNC_CPed__SpawnAt;
		static CPed__SetModel_t						FUNC_CPed__SetModel;

		static GtaThread__Constructor_t				FUNC_GtaThread__Constructor;

		static CPool__Allocate_t					FUNC_CPool__Allocate;


		// Pointers
		static DWORD64						PTR_PedFactory;
		static DWORD64						PTR_ThreadManager;
		static DWORD64						PTR_CurrentThread;
		static DWORD64						PTR_PlayerInfoPool;
		static DWORD64						PTR_PedPool;

		// Variables
		static DWORD64						VAR_GameState;
		static DWORD64						VAR_ThreadsCount;
		static DWORD64						VAR_TlsIndex;

		// Arrays


};

#endif