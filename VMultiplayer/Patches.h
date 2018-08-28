/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Patches.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef PATCHES_H
#define PATCHES_H

class CPatches
{
	public:
		static void InstallFunctionDisablePatch(DWORD64 dwFunction, WORD wReturn);
		static void InstallCustomPatch(DWORD64 dwAddress, BYTE bytePatch[], int iLength);
		static void InstallNopPatch(DWORD64 dwAddress, int iSize);

		static void InstallPatches();

};

#endif