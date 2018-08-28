/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VEntity.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VENTITY_H
#define VENTITY_H

// Only applies to V types
enum eVEntityType
{
	VENTITY_TYPE_PED = 4
};

#pragma pack(push, 1)
class VRagefwEntity
{
public:
	PAD(pad0, 0x28);					// 0x00000 - 0x00028
	BYTE			byteType;			// 0x00028 - 0x00029
	PAD(pad1, 0x67);					// 0x00029 - 0x00090
	CVector3		vecPosition;		// 0x00090 - 0x0009C
	PAD(pad2, 0x1D);					// 0x0009C - 0x000B9
	// Size = 0x000B9
};
#pragma pack(pop)

#pragma pack(push, 1)
class VEntity : public VRagefwEntity
{
public:
	// rage::fwEntity					// 0x00000 - 0x000B9
	PAD(pad0, 0x13);					// 0x000B9 - 0x000CC
	// Size = 0xCC
};
#pragma pack(pop)

class CVEntity : public CVObjectBase<VEntity>
{
public:
	CVEntity(VEntity *pEntity);
	CVEntity(VEntity *pEntity, DWORD dwEntityId);
	~CVEntity();

	CVector3 GetPosition();
	void SetPosition(CVector3 vecPosition);

	DWORD GetID() { return m_dwGameId; };
	void SetID(DWORD dwGameId) { m_dwGameId = dwGameId; };

private:
	DWORD	m_dwGameId;
};

#endif