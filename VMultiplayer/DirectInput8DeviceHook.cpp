/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: DirectInput8Device.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: DirectInput8 interface hook source file
=============================================================*/

#include "Main.h"

CDirectInputDevice8Hook::CDirectInputDevice8Hook(IDirectInput8 *pDirectInput, IDirectInputDevice8 *pDirectInputDevice, GUID guidType)
{
	// Save device parameters
	m_pDirectInput = pDirectInput;
	m_pDirectInputDevice = pDirectInputDevice;
	m_guidType = guidType;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_pDirectInputDevice->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE CDirectInputDevice8Hook::AddRef()
{
	return m_pDirectInputDevice->AddRef();
}

ULONG STDMETHODCALLTYPE CDirectInputDevice8Hook::Release()
{
	ULONG ulReturn = m_pDirectInputDevice->Release();
	// If the reference count is 0 delete ourselves
	if (ulReturn == 0)
		delete this;

	return ulReturn;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::GetCapabilities(LPDIDEVCAPS p0)
{
	return m_pDirectInputDevice->GetCapabilities(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA p0, LPVOID p1, DWORD p2)
{
	return m_pDirectInputDevice->EnumObjects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::GetProperty(REFGUID rguid, LPDIPROPHEADER p1)
{
	return m_pDirectInputDevice->GetProperty(rguid, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::SetProperty(REFGUID rguid, LPCDIPROPHEADER p1)
{
	return m_pDirectInputDevice->SetProperty(rguid, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::Acquire()
{
	return m_pDirectInputDevice->Acquire();
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::Unacquire()
{
	return m_pDirectInputDevice->Unacquire();
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::GetDeviceState(DWORD p0, LPVOID p1)
{
	// Get the device state
	HRESULT hResult = m_pDirectInputDevice->GetDeviceState(p0, p1);
	// Check if we have a disabled input
	if (!CCore::GetMultiplayer()->GetInputState())
		// Dont process input
		memset(p1, 0, p0);

	return hResult;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::GetDeviceData(DWORD p0, LPDIDEVICEOBJECTDATA p1, LPDWORD p2, DWORD p3)
{
	HRESULT hResult = m_pDirectInputDevice->GetDeviceData(p0, p1, p2, p3);
	return hResult;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::SetDataFormat(LPCDIDATAFORMAT p0)
{
	return m_pDirectInputDevice->SetDataFormat(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::SetEventNotification(HANDLE p0)
{
	return m_pDirectInputDevice->SetEventNotification(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::SetCooperativeLevel(HWND p0, DWORD p1)
{
	return m_pDirectInputDevice->SetCooperativeLevel(p0, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA p0, DWORD p1, DWORD p2)
{
	return m_pDirectInputDevice->GetObjectInfo(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::GetDeviceInfo(LPDIDEVICEINSTANCEA p0)
{
	return m_pDirectInputDevice->GetDeviceInfo(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::RunControlPanel(HWND p0, DWORD p1)
{
	return m_pDirectInputDevice->RunControlPanel(p0, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::Initialize(HINSTANCE p0, DWORD p1, REFGUID rguid)
{
	return m_pDirectInputDevice->Initialize(p0, p1, rguid);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::CreateEffect(REFGUID rguid, LPCDIEFFECT p1, LPDIRECTINPUTEFFECT * p2, LPUNKNOWN p3)
{
	return m_pDirectInputDevice->CreateEffect(rguid, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::EnumEffects(LPDIENUMEFFECTSCALLBACKA p0, LPVOID p1, DWORD p2)
{
	return m_pDirectInputDevice->EnumEffects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::GetEffectInfo(LPDIEFFECTINFOA p0, REFGUID rguid)
{
	return m_pDirectInputDevice->GetEffectInfo(p0, rguid);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::GetForceFeedbackState(LPDWORD p0)
{
	return m_pDirectInputDevice->GetForceFeedbackState(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::SendForceFeedbackCommand(DWORD p0)
{
	return m_pDirectInputDevice->SendForceFeedbackCommand(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK p0, LPVOID p1, DWORD p2)
{
	return m_pDirectInputDevice->EnumCreatedEffectObjects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::Escape(LPDIEFFESCAPE p0)
{
	return m_pDirectInputDevice->Escape(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::Poll()
{
	return m_pDirectInputDevice->Poll();
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::SendDeviceData(DWORD p0, LPCDIDEVICEOBJECTDATA p1, LPDWORD p2, DWORD p3)
{
	return m_pDirectInputDevice->SendDeviceData(p0, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::EnumEffectsInFile(LPCSTR p0, LPDIENUMEFFECTSINFILECALLBACK p1, LPVOID p2, DWORD p3)
{
	return m_pDirectInputDevice->EnumEffectsInFile(p0, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::WriteEffectToFile(LPCSTR p0, DWORD p2, LPDIFILEEFFECT p3, DWORD p4)
{
	return m_pDirectInputDevice->WriteEffectToFile(p0, p2, p3, p4);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::BuildActionMap(LPDIACTIONFORMATA p0, LPCSTR p1, DWORD p2)
{
	return m_pDirectInputDevice->BuildActionMap(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::SetActionMap(LPDIACTIONFORMATA p0, LPCSTR p1, DWORD p2)
{
	return m_pDirectInputDevice->SetActionMap(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Hook::GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA p0)
{
	return m_pDirectInputDevice->GetImageInfo(p0);
}
