/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPlayerInfoPool.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VPLAYERINFOPOOL_H
#define VPLAYERINFOPOOL_H

class CVPlayerInfoPool : public CVPool<VPlayerInfo>
{
public:
	CVPlayerInfoPool(VPool *pPool);

private:
};

#endif