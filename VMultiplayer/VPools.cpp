/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPools.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CVPedPool			*CVPools::m_pPedPool = NULL;
CVPlayerInfoPool	*CVPools::m_pPlayerInfoPool = NULL;

void CVPools::Initialize()
{
	// Create pools
	m_pPedPool = new CVPedPool(*(VPool **)CAddress::PTR_PedPool);
	m_pPlayerInfoPool = new CVPlayerInfoPool(*(VPool **)CAddress::PTR_PlayerInfoPool);
};