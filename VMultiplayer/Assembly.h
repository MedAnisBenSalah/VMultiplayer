/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Assembly.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef ASSEMBLY_H
#define ASSEMBLY_H

extern "C" DWORD64 GetCaller(DWORD64 dwStackSub);
extern "C" DWORD64 GetTEB(DWORD64 dwTlsIndex);
extern "C" float SHUFPS_55(float fArg1, float fArg2);
extern "C" float SHUFPS_AA(float fArg1, float fArg2);
extern "C" float SHUFPS_FF(float fArg1, float fArg2);

#endif