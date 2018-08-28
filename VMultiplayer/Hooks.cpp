/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Hooks.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/


#include "Main.h"

// Global pointers
CIDXGISwapChainHook			*pSwapChainHook = NULL;

// A flag to indicate whether or not we should hook the swap chain
static BYTE bSwapChainFirst;
static BYTE bSwapChainHookReady;
// A handle the D3D11 library
static HMODULE hD3D11Library = NULL;

// Type definition for LoadLibrary function
typedef HMODULE(WINAPI* LoadLibrary_t)(LPCSTR mod);
// Type definition for FreeLibrary function
typedef HMODULE(WINAPI* FreeLibrary_t)(HMODULE hLibrary);
// Type defition for DirectInput8Create
typedef HRESULT(WINAPI* DirectInput8Create_t)(HINSTANCE hInstance, DWORD dwVersion, REFIID refiid, LPVOID *ppOut, LPUNKNOWN lpUnknown);
// Type defition for NtQueryInformationProcess
typedef HRESULT(WINAPI* NtQueryInformationProcess_t)(HANDLE hProcess, PROCESSINFOCLASS processInfo, PVOID pInformation, ULONG ulInformationLength,
	PULONG pulReturnedLength);
// Type definition for D3D11CreateDevice function
typedef HRESULT(WINAPI* D3D11CreateDeviceAndSwapChain_t)(IDXGIAdapter *pAdapter, D3D_DRIVER_TYPE driverType, HMODULE hModule, UINT uiFlags,
	const D3D_FEATURE_LEVEL *pFeatureLevels, UINT uiFeatureLevels, UINT uiSDKVersion, const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
	IDXGISwapChain **ppSwapChain, ID3D11Device **ppDevice, D3D_FEATURE_LEVEL *pFeatureLevel, ID3D11DeviceContext **ppImmediateContext);

typedef HMODULE(WINAPI* IsDebuggerPresent_t)();

// Pointers to the functions's trampolines
LoadLibrary_t						pfn_LoadLibrary = NULL;
FreeLibrary_t						pfn_FreeLibrary = NULL;
D3D11CreateDeviceAndSwapChain_t		pfn_D3D11CreateDeviceAndSwapChain = NULL;
DirectInput8Create_t				pfn_DirectInput8Create = NULL;
IsDebuggerPresent_t					pfn_IsDebuggerPresent = NULL;
NtQueryInformationProcess_t			pfn_NtQueryInformationProcess = NULL;

// Hook for the D3D11CreateDeviceAndSwapChain function
HRESULT WINAPI D3D11CreateDeviceAndSwapChain_Hook(IDXGIAdapter *pAdapter, D3D_DRIVER_TYPE driverType, HMODULE hModule, UINT uiFlags, 
	const D3D_FEATURE_LEVEL *pFeatureLevels, UINT uiFeatureLevels, UINT uiSDKVersion, const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc, 
	IDXGISwapChain **ppSwapChain, ID3D11Device **ppDevice, D3D_FEATURE_LEVEL *pFeatureLevel, ID3D11DeviceContext **ppImmediateContext)
{
	LOG("D3D11CreateDeviceAndSwapChain_Hook");
	// Validate the function pointer
	if (!pfn_D3D11CreateDeviceAndSwapChain)
		return NULL;

	// Create the device
	HRESULT hResult = pfn_D3D11CreateDeviceAndSwapChain(pAdapter, driverType, hModule, uiFlags, pFeatureLevels, uiFeatureLevels, 
		uiSDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);

	// Validate the device creation
	if (SUCCEEDED(hResult) && bSwapChainHookReady)
	{
		LOG("D3D11CreateDeviceAndSwapChain_Hook - Created device (0x%x)", *ppDevice);
		// Create our hook interface
		// NOTE: We don't need a hook for ID3D11Device now, but it might come to use later
		/*CDirect3D11DeviceHook *pDirect3D11DeviceHook = NULL;
		pDirect3D11DeviceHook = new CDirect3D11DeviceHook(*ppDevice);*/
		// Create our swap chain hook interface
		pSwapChainHook = new CIDXGISwapChainHook(*ppSwapChain, *ppDevice, *ppImmediateContext);
		// Redirect the swap chain to use our pointer
		*ppSwapChain = pSwapChainHook;
		// Initialize the graphics
		CCore::GetGraphics()->Initialize(pSwapChainDesc->BufferDesc.Width, pSwapChainDesc->BufferDesc.Height, *ppDevice);
		// Set the current HWND
		CCore::SetHWND(pSwapChainDesc->OutputWindow);
		// Change the window title
		SetWindowText(pSwapChainDesc->OutputWindow, NAME " v" VERSION);
	}
	// Are we in the first call
	if (bSwapChainFirst)
		bSwapChainHookReady = true;

	LOG("D3D11CreateDeviceAndSwapChain_Hook Done");
	return hResult;
}

// Hook for the DirectInput8Create function
HRESULT WINAPI DirectInput8Create_Hook(HINSTANCE hInstance, DWORD dwVersion, REFIID refiid, LPVOID *ppOut, LPUNKNOWN lpUnkown)
{
	LOG("DirectInput8Create_Hook");
	// Validate the function pointer
	if(!pfn_DirectInput8Create) 
		return NULL;

	// Create the DirectInput
	HRESULT hResult = pfn_DirectInput8Create(hInstance, dwVersion, refiid, ppOut, lpUnkown);
	if (SUCCEEDED(hResult))
		// Redirect the pointer to use our hook class
		*ppOut = new CDirectInput8Hook((CDirectInput8Hook *)*ppOut);
	
	// Return
	LOG("DirectInput8Create_Hook Done");
	return hResult;
}

HMODULE WINAPI LoadLibrary_Hook(LPCSTR lpModule)
{
	// Load the library
	HMODULE hLibrary = pfn_LoadLibrary(lpModule);
	// Are we loading D3D11 ?
	if ((!strcmp(lpModule, "D3D11.DLL") || !strcmp(lpModule, "d3d11.dll")))
	{
		LOG("LoadLibrary_Hook(%s)", lpModule);
		// Do we have a valid library handle ?
		if (hD3D11Library)
		{
			// Uninstall the D3D11 hook
			MH_RemoveHook((BYTE *)GetProcAddress(hLibrary, "D3D11CreateDeviceAndSwapChain"));
			// Mark it as first call
			bSwapChainFirst = true;
		}
		// Install hook for D3D11CreateDeviceAndSwapChain
		pfn_D3D11CreateDeviceAndSwapChain = (D3D11CreateDeviceAndSwapChain_t)CHooks::InstallDetoursHook((BYTE *)GetProcAddress(hLibrary,
			"D3D11CreateDeviceAndSwapChain"), (PBYTE)D3D11CreateDeviceAndSwapChain_Hook);

		// Set the D3D11 library
		hD3D11Library = hLibrary;
		LOG("LoadLibrary_Hook Done");
	}
	return hLibrary;
}

HMODULE WINAPI FreeLibrary_Hook(HMODULE hLibrary)
{
	// Is it unloading D3D11.dll
	if (hLibrary == hD3D11Library)
	{
		LOG("FreeLibrary_Hook(0x%x)", hLibrary);
		// Uninstall the D3D11 hook
		MH_RemoveHook((BYTE *)GetProcAddress(hLibrary, "D3D11CreateDeviceAndSwapChain"));
		// Reset the module handle
		hD3D11Library = NULL;
		LOG("FreeLibrary_Hook Done");
	}
	return pfn_FreeLibrary(hLibrary);
}

BOOL WINAPI IsDebuggerPresent_Hook()
{
	// Makes our life a lot easier by allowing us to debug the game
	return FALSE;
}

BOOL WINAPI NtQueryInformationProcess_Hook(HANDLE hProcess, PROCESSINFOCLASS processInfo, PVOID pInformation, ULONG ulInformationLength,
	PULONG pulReturnedLength)
{
	// Call the real function
	BOOL bReturn = pfn_NtQueryInformationProcess(hProcess, processInfo, pInformation, ulInformationLength, pulReturnedLength);
	// Check if its debugging protection
	if (processInfo == 0x0)
	{
		// Get the process info class
		PROCESS_BASIC_INFORMATION *ProcessInfo = reinterpret_cast<PROCESS_BASIC_INFORMATION *>(pInformation);
		// Remove the anti-debugging protection
		ProcessInfo->PebBaseAddress->BeingDebugged = 0;
	}
	return bReturn;
}

bool CHooks::InstallAPIHooks()
{
	// Initialize MinHook
	if (MH_Initialize() != MH_OK)
		return false;

	// Reset swap chain ready flags
	bSwapChainFirst = false;
	bSwapChainHookReady = false;
	// Hook for LoadLibrary (to catch the loading of D3D11.dll)
	pfn_LoadLibrary = (LoadLibrary_t)InstallDetoursHook((BYTE *)GetProcAddress(GetModuleHandle("Kernel32.dll"),
		"LoadLibraryA"), (PBYTE)LoadLibrary_Hook);

	// Hook for FreeLibrary (to catch the unloading of D3D11.dll)
	pfn_FreeLibrary = (FreeLibrary_t)InstallDetoursHook((BYTE *)GetProcAddress(GetModuleHandle("Kernel32.dll"),
		"FreeLibrary"), (PBYTE)FreeLibrary_Hook);

	// Hook for DirectInput8Create
	pfn_DirectInput8Create = (DirectInput8Create_t)InstallDetoursHook((BYTE *)GetProcAddress(GetModuleHandle("dinput8.dll"),
		"DirectInput8Create"), (PBYTE)DirectInput8Create_Hook);

	// Hook for IsDebuggerPresent
	pfn_IsDebuggerPresent = (IsDebuggerPresent_t)InstallDetoursHook((BYTE *)GetProcAddress(GetModuleHandle("Kernel32.dll"),
		"IsDebuggerPresent"), (PBYTE)IsDebuggerPresent_Hook);

	// Hook for NtQueryInformationProcess
	pfn_NtQueryInformationProcess = (NtQueryInformationProcess_t)InstallDetoursHook((BYTE *)GetProcAddress(GetModuleHandle("ntdll.dll"),
		"NtQueryInformationProcess"), (PBYTE)NtQueryInformationProcess_Hook);

	// Install window hook
	CWindowHook::Install();
	return true;
}

void CHooks::InstallGameHooks()
{
	// Install all hooks
	CGameHooks::Install();
}

void CHooks::UninstallHooks()
{
	// Remove all hooks
	MH_RemoveHook(MH_ALL_HOOKS);
	// Uninitialize MinHooks
	MH_Uninitialize();
}

PBYTE CHooks::InstallDetoursHook(PBYTE pbyteInstallAddress, PBYTE pbyteHookAddress)
{
	BYTE *pbyteTrampoline;
	int iReturnError;
	// Install hook
	if ((iReturnError = MH_CreateHook(pbyteInstallAddress, pbyteHookAddress, reinterpret_cast<LPVOID *>(&pbyteTrampoline))) != MH_OK)
	{
		LOG("CHooks::InstallDetoursHook - MH_CreateHook failed (%d)", iReturnError);
		return NULL;
	}
	// Enable the hook
	if ((iReturnError = MH_EnableHook(pbyteInstallAddress)) != MH_OK)
	{
		LOG("CHooks::InstallDetoursHook - MH_EnableHook failed (%d)", iReturnError);
		return NULL;
	}
	return pbyteTrampoline;
}

void CHooks::InstallCallHook(DWORD64 dwInstallAddress, DWORD64 dwHookFunction)
{
	// Unprotect the address
	CUtility::Unprotect(dwInstallAddress, 5);
	// Calculate the installing address
	DWORD64 dwFunction = dwHookFunction - (dwInstallAddress + 5);
	// Write the call instruction
	*(BYTE *)dwInstallAddress = 0xE8;
	// Write the hook function address
	*(DWORD64 *)(dwInstallAddress + 1) = dwFunction;
}

BYTE byteJmpHook[] = { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00 };

void CHooks::InstallJmpHook(DWORD64 dwInstallAddress, DWORD64 dwHookFunction)
{
	// Unprotect the address
	CUtility::Unprotect(dwInstallAddress, 20);
	// Calculate the installing address
	/*DWORD64 dwFunction = dwHookFunction - (dwInstallAddress + 5);
	// Write the call instruction
	*(BYTE *)dwInstallAddress = 0xE9;
	// Write the hook function address
	*(DWORD *)(dwInstallAddress + 1) = (DWORD)dwFunction;*/
	// Write the jmp hook
	memcpy(reinterpret_cast<VOID*>(dwInstallAddress), reinterpret_cast<VOID*>(byteJmpHook), sizeof(byteJmpHook));
	// Write the destination address
	*(DWORD64*)(dwInstallAddress + 0x6) = dwHookFunction;

}

void CHooks::InstallAddressHook(DWORD64 dwInstallAddress, DWORD64 dwHookFunction)
{
	// Unprotect the address
	CUtility::Unprotect(dwInstallAddress, 5);
	// Write the hook function address
	*(DWORD64 *)(dwInstallAddress) = dwHookFunction;
}
