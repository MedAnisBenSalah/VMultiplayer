/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPools.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VPOOLS_H
#define VPOOLS_H

class CVPools
{
public:
	static void Initialize();

	static CVPedPool *GetPedPool() { return m_pPedPool; };
	static CVPlayerInfoPool *GetPlayerInfoPool() { return m_pPlayerInfoPool; };

private:
	static CVPedPool					*m_pPedPool;
	static CVPlayerInfoPool				*m_pPlayerInfoPool;
};

#endif