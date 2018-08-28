/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPhyscial.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CVPhysical::CVPhysical(VPhysical *pPhysical) : CVDynamicEntity(reinterpret_cast<VDynamicEntity *>(pPhysical))
{
}

CVPhysical::~CVPhysical()
{

}