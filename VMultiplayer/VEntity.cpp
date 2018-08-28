/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VEntity.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CVEntity::CVEntity(VEntity *pEntity)
{
	// Set the entity interface
	SetInterface(pEntity);
	// Reset entity id
	m_dwGameId = -1;
}

CVEntity::CVEntity(VEntity *pEntity, DWORD dwEntityId)
{
	// Set the entity interface
	SetInterface(pEntity);
	// Set entity id
	m_dwGameId = dwEntityId;
}

CVEntity::~CVEntity()
{

}

CVector3 CVEntity::GetPosition()
{
	// Validate the interface
	if (!GetInterface())
		return CVector3();

	return GetInterface()->vecPosition;
}

void CVEntity::SetPosition(CVector3 vecPosition)
{
	// Validate the interface
	if (GetInterface())
		GetInterface()->vecPosition = vecPosition;
}