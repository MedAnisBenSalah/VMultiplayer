/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPedPool.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VPEDPOOL_H
#define VPEDPOOL_H

class CVPedPool : public CVPool<VPed>
{
public:
	CVPedPool(VPool *pPool);
	~CVPedPool();

private:
};

#endif