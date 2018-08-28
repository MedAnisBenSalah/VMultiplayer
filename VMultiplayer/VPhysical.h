/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPed.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VPHYSCIAL_H
#define VPHYSCIAL_H

#pragma pack(push, 1)
class VPhysical : public VDynamicEntity
{
public:
	// VDynamicEntity					// 0x00000 - 0x000F8
	PAD(pad0, 0x1A0);					// 0x000F8 - 0x00298
	// Size = 0x298
};
#pragma pack(pop)

class CVPhysical : public CVDynamicEntity
{
public:
	CVPhysical(VPhysical *pPhysical);
	~CVPhysical();

private:
};

#endif