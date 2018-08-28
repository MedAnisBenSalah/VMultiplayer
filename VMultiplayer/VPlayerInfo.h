/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPlayerInfo.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VPLAYERINFO_H
#define VPLAYERINFO_H

// To avoid having errors due to unknown VPed type
class VPed;

#pragma pack(push, 1)
class VPlayerUnknown
{
public:
	PAD(pad0, 0x4C);						// 0x00000 - 0x0004C
	char		*szName;					// 0x0004C - 0x00054
};
#pragma pack(pop)

#pragma pack(push, 1)
class VPlayerInfo
{
public:
	PAD(pad0, 0x20);						// 0x00000 - 0x00020
	VPlayerUnknown		*pPlayerUnknown;	// 0x00020 - 0x00028
	PAD(pad1, 0xF8);						// 0x00028 - 0x00120
	VPed				*pPed;				// 0x00120 - 0x00128
};
#pragma pack(pop)

class CVPlayerInfo : public CVObjectBase<VPlayerInfo>
{
public:
	CVPlayerInfo(VPlayerInfo *pPlayerInfo);
	~CVPlayerInfo();

	void SetPed(VPed *pPed);
	VPed *GetPed();

private:
};

#endif