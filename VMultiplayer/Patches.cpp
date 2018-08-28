/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Patches.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

void CPatches::InstallFunctionDisablePatch(DWORD64 dwFunction, WORD wReturn = 0)
{
	// Unprotect the the function
	CUtility::Unprotect(dwFunction, wReturn == 0 ? 1 : 2);
	// Write a retn patch
	*(BYTE *)(dwFunction) = 0xC3;
	// Write the return value
	if (wReturn != 0)
		*(WORD *)(dwFunction + 1) = wReturn;
	else
		*(WORD *)(dwFunction + 1) = 0x9090;
}

void CPatches::InstallNopPatch(DWORD64 dwAddress, int iSize)
{
	// Unprotect the the address
	CUtility::Unprotect(dwAddress, iSize);
	// Write a NOP patch
	memset((void *)dwAddress, 0x90, iSize);
}

void CPatches::InstallCustomPatch(DWORD64 dwAddress, BYTE bytePatch[], int iLength)
{
	// Unprotect the address
	CUtility::Unprotect(dwAddress, iLength);
	// Write the patch
	memcpy((void *)dwAddress, bytePatch, iLength);
}

// xor eax, eax \ ret
BYTE byteReturnNullPatch[] = { 0x33, 0xC0, 0xC3, 0x90, 0x90 };

void CPatches::InstallPatches()
{
	// Disable population
	InstallCustomPatch(CAddress::CALLBACK_CPopulation__CreatePed, byteReturnNullPatch, sizeof(byteReturnNullPatch));
	InstallCustomPatch(CAddress::CALLBACK_CPopulation__CreateVehicle, byteReturnNullPatch, sizeof(byteReturnNullPatch));
	// Disable parked vehicles
	InstallCustomPatch(CAddress::CALLBACK_CPopulation__CreateParkedVehicle, byteReturnNullPatch, sizeof(byteReturnNullPatch));
}
