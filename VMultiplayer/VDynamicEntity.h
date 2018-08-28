/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VDynamicEntity.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VDYNAMICENTITY_H
#define VDYNAMICENTITY_H

#pragma pack(push, 1)
class VDynamicEntity : public VEntity
{
public:
	//	VEntity							// 0x00000 - 0x000CC
	PAD(pad0, 0x2C);					// 0x000CC - 0x000F8
	// Size = 0xF8
};
#pragma pack(pop)

class CVDynamicEntity : public CVEntity
{
public:
	CVDynamicEntity(VDynamicEntity *pDynamicEntity);
	~CVDynamicEntity();

private:
};

#endif