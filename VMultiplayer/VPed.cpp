/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPed.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CVPed::CVPed(VPed *pPed) : CVPhysical(reinterpret_cast<VPhysical *>(pPed))
{
	// Set the entity id to the current ped id
	if (pPed)
		SetID(GetPedID());
}

CVPed::~CVPed()
{

}

void CVPed::SetPlayerInfo(VPlayerInfo *pPlayerInfo)
{
	if (GetInterface())
		GetInterface<VPed>()->pPlayerInfo = pPlayerInfo;
}

VPlayerInfo *CVPed::GetPlayerInfo()
{
	if (GetInterface())
		return GetInterface<VPed>()->pPlayerInfo;
	else
		return NULL;
}

DWORD CVPed::GetPedID()
{
	// Validate the interface
	if (!GetInterface())
		return -1;

	// Get the ped id
	return CAddress::FUNC_CPed__GetID(reinterpret_cast<VPed *>(GetInterface()));
}

void CVPed::SpawnAt(CVector3 vecPosition)
{
	// Validate the interface
	if (!GetInterface())
		return;

	// Spawn the ped
	CAddress::FUNC_CPed__SpawnAt(reinterpret_cast<VPed *>(GetInterface()), vecPosition.fX, vecPosition.fY, vecPosition.fZ, 1, 1, 18);
}

void CVPed::SetModel(VModelInfo *pModelInfo)
{
	// Validate the interface
	if (!GetInterface())
		return;

	CAddress::FUNC_CPed__SetModel(GetInterface<VPed>(), pModelInfo);
}