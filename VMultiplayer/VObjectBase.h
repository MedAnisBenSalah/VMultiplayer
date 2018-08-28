/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VObjectBase.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VOBJECTBASE_H
#define VOBJECTBASE_H

template <typename T>
class CVObjectBase
{
public:
	void SetInterface(T *pInterface) { m_pInterface = pInterface; };
	T   *GetInterface() { return m_pInterface; };

	template <typename Y>
	Y   *GetInterface() { return reinterpret_cast<Y *>(m_pInterface); };


private:
	T		*m_pInterface;
};

#endif