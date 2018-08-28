/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Direct3D11DeviceHook.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

CDirect3D11DeviceHook::CDirect3D11DeviceHook(ID3D11Device *pDevice)
{ 
	// Save the device
	m_pDevice = pDevice;
}

CDirect3D11DeviceHook::~CDirect3D11DeviceHook(void)
{

}

HRESULT CDirect3D11DeviceHook::QueryInterface(REFIID riid, void** ppvObj)
{
	*ppvObj = NULL;
	HRESULT hRes = m_pDevice->QueryInterface(riid, ppvObj);
	if (hRes == NOERROR)
	{
		*ppvObj = this;
	}
	return hRes;
}

ULONG CDirect3D11DeviceHook::AddRef(void)
{
	return(m_pDevice->AddRef());
}

ULONG CDirect3D11DeviceHook::Release(void)
{
	ULONG uCount = m_pDevice->Release();
	if(uCount == 0)
		delete this;

	return uCount;
}