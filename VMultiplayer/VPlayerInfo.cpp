/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPlayerInfo.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CVPlayerInfo::CVPlayerInfo(VPlayerInfo *pPlayerInfo)
{
	// Set interface
	SetInterface(pPlayerInfo);
}

CVPlayerInfo::~CVPlayerInfo()
{

}

void CVPlayerInfo::SetPed(VPed *pPed)
{
	if (GetInterface())
		GetInterface()->pPed = pPed;
}

VPed *CVPlayerInfo::GetPed()
{
	if (GetInterface())
		return GetInterface()->pPed;
	else
		return NULL;
}
