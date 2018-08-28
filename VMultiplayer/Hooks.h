/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Hooks.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef HOOKS_H
#define HOOKS_H

class CHooks
{
	public:
		static bool InstallAPIHooks();
		static void InstallGameHooks();
		static void UninstallHooks();

		static BYTE *InstallDetoursHook(BYTE *pbyteInstallAddress, BYTE *pbyteHookAddress);
		static void InstallCallHook(DWORD64 dwInstallAddress, DWORD64 dwHookFunction);
		static void InstallJmpHook(DWORD64 dwInstallAddress, DWORD64 dwHookFunction);
		static void InstallAddressHook(DWORD64 dwInstallAddress, DWORD64 dwHookFunction);


};

#endif