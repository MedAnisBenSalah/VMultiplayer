/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VPool.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VPOOL_H
#define VPOOL_H

#pragma pack(push, 1)
class VPool
{
public:
	DWORD64			dwElementSize;				// 0x00000 - 0x00008
	void			*pElements;					// 0x00008 - 0x00010
};
#pragma pack(pop)

template <typename T> 
class CVPool : public CVObjectBase<VPool>
{
public:
	CVPool(VPool *pPool)
	{
		// Set the pool interface
		SetInterface(pPool);
	};

	~CVPool()
	{
	};

	T *Allocate()
	{
		if (GetInterface())
			return reinterpret_cast<T *>(CAddress::FUNC_CPool__Allocate(GetInterface()));
		else
			return NULL;
	};

private:

};

#endif