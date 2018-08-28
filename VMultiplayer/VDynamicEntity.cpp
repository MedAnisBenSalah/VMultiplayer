/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VDynamicEntity.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CVDynamicEntity::CVDynamicEntity(VDynamicEntity *pDynamicEntity) : CVEntity(reinterpret_cast<VEntity *>(pDynamicEntity))
{
}

CVDynamicEntity::~CVDynamicEntity()
{

}