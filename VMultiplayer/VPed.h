/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPed.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VPED_H
#define VPED_H

#pragma pack(push, 1)
class VMatrix
{
public:
	PAD(pad0, 0x90);				// 0x00000 - 0x00090
	CVector3	vecPosition;		// 0x00090 - 0x0009C
};
#pragma pack(pop)
class VPed;

#pragma pack(push, 1)
class VPedIKManager
{
public:
	PAD(pad0, 0x160);
	VPed *pPed;
};
#pragma pack(pop)

#pragma pack(push, 1)
class VPed : public VPhysical
{
public:
	// VPhysical						// 0x00000 - 0x00298
	PAD(pad0, 0xC28);					// 0x00298 - 0x00EC0
	VPedIKManager		*pIKManager;	// 0x00EC0 - 0x00EC8
	PAD(pad1, 0x1B0);					// 0x00EC8 - 0x01078
	VPlayerInfo			*pPlayerInfo;	// 0x01078 - 0x01080
	//VMatrix		*pMatrix;			// 0x01488 - 0x01490
	// Size = 0x18D4
};
#pragma pack(pop)

class CVPed : public CVPhysical
{
public:
	CVPed(VPed *pPed);
	~CVPed();

	void SetPlayerInfo(VPlayerInfo *pPlayerInfo);
	VPlayerInfo *GetPlayerInfo();

	// Direct game functions
	DWORD GetPedID();
	void  SpawnAt(CVector3 vecPosition);
	void  SetModel(VModelInfo *pModelInfo);

private:
};

#endif