/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: DirectInput8.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: DirectInput8 interface hook source file
=============================================================*/

#include "Main.h"

CDirectInput8Hook::CDirectInput8Hook(IDirectInput8 *pDirectInput)
{
	// Save the DirectInput pointer
	m_pDirectInput = pDirectInput;
}

HRESULT STDMETHODCALLTYPE CDirectInput8Hook::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_pDirectInput->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE CDirectInput8Hook::AddRef()
{
	return m_pDirectInput->AddRef();
}

ULONG STDMETHODCALLTYPE CDirectInput8Hook::Release()
{
	ULONG uRet = m_pDirectInput->Release();

	// If the reference count is 0 delete ourselves
	if(uRet == 0)
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE CDirectInput8Hook::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A * lplpDirectInputDevice, LPUNKNOWN pUknOuter)
{
	// Create the dinput device
	HRESULT hResult = m_pDirectInput->CreateDevice(rguid, lplpDirectInputDevice, pUknOuter);
	if (SUCCEEDED(hResult))
		// Redirect the pointer to use our hook class
		*lplpDirectInputDevice = new CDirectInputDevice8Hook(this, *lplpDirectInputDevice, rguid);

	return hResult;
}

HRESULT STDMETHODCALLTYPE CDirectInput8Hook::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_pDirectInput->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Hook::GetDeviceStatus(REFGUID rguidInstance)
{
	return m_pDirectInput->GetDeviceStatus(rguidInstance);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Hook::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return m_pDirectInput->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Hook::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return m_pDirectInput->Initialize(hinst, dwVersion);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Hook::FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance)
{
	return m_pDirectInput->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Hook::EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_pDirectInput->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Hook::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return m_pDirectInput->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}
