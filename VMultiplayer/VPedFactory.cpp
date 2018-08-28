/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPedFactory.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CVPedFactory::CVPedFactory(VPedFactory *pInterface)
{
	// Set the interface
	SetInterface(pInterface);
}

CVPedFactory::~CVPedFactory()
{

}

VPed *CVPedFactory::GetLocalPlayer()
{
	if (!GetInterface())
		return NULL;

	return GetInterface()->pLocalPlayer;
}

typedef bool(*CPedFactory__DeletePed_t)(VPedFactory *pPedFactory, VPed *pPed, bool bUnknown);
CPedFactory__DeletePed_t FUNC_CPedFactory__DeletePed;

bool CVPedFactory::DeletePed(VPed *pPed)
{
	if (!GetInterface())
		return false;

	// Delete the ped
	DWORD64 dwTest = (DWORD64)pPed;
	dwTest = *(DWORD64 *)(dwTest + 8);
	FUNC_CPedFactory__DeletePed = (CPedFactory__DeletePed_t)(CCore::GetBaseAddress() + 0x1401DBF88);
	return FUNC_CPedFactory__DeletePed(GetInterface(), (VPed *)dwTest, false);
}