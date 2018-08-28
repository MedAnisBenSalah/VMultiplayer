/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPedFactory.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VPEDFACTORY_H
#define VPEDFACTORY_H

#pragma pack(push, 1)
class VPedFactory
{
public:
	PAD(pad0, 0x8);				// 0x0000 - 0x0008
	VPed	*pLocalPlayer;		// 0x0008 - 0x0010
};
#pragma pack(pop)

class CVPedFactory : public CVObjectBase<VPedFactory>
{
public:
	CVPedFactory(VPedFactory *pInterface);
	~CVPedFactory();

	 VPed		*GetLocalPlayer();

	 // Direct game functions
	 bool DeletePed(VPed *pPed);
};

#endif