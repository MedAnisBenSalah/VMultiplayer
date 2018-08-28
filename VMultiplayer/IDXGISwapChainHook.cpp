/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: IDXGISwapChainHook.cpp
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"
#include <D3DX11.h>
#include <d3dx10.h>

CIDXGISwapChainHook::CIDXGISwapChainHook(IDXGISwapChain *pSwapChain, ID3D11Device *pDevice, ID3D11DeviceContext *pContext)
{ 
	// Save pointers
	m_pSwapChain = pSwapChain;
	m_pDevice = pDevice;
	m_pDeviceContext = pContext;
}

CIDXGISwapChainHook::~CIDXGISwapChainHook(void)
{

}

HRESULT CIDXGISwapChainHook::QueryInterface(REFIID riid, void** ppvObj)
{
	*ppvObj = NULL;
	HRESULT hRes = m_pSwapChain->QueryInterface(riid, ppvObj);
	if (hRes == NOERROR)
	{
		*ppvObj = this;
	}
	return hRes;
}

ULONG CIDXGISwapChainHook::AddRef(void)
{
	return m_pSwapChain->AddRef();
}

ULONG CIDXGISwapChainHook::Release(void)
{
	ULONG uCount = m_pSwapChain->Release();
	if (uCount == 0)
		delete this;

	return uCount;
}

HRESULT CIDXGISwapChainHook::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
	return m_pSwapChain->SetPrivateData(Name, DataSize, pData);
}

HRESULT CIDXGISwapChainHook::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
	return m_pSwapChain->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT CIDXGISwapChainHook::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
	return m_pSwapChain->GetPrivateData(Name, pDataSize, pData);
}

HRESULT CIDXGISwapChainHook::GetParent(REFIID riid, void **ppParent)
{
	return m_pSwapChain->GetParent(riid, ppParent);
}

HRESULT CIDXGISwapChainHook::GetDevice(REFIID riid, void **ppDevice)
{
	return m_pSwapChain->GetDevice(riid, ppDevice);
}

HRESULT CIDXGISwapChainHook::Present(UINT SyncInterval, UINT Flags)
{
	// Render GUI
	if (CCore::GetGraphics()->GetGUI())
		CCore::GetGraphics()->GetGUI()->Render();

	// Call the present function
	HRESULT hResult = m_pSwapChain->Present(SyncInterval, Flags);
	// Check for device loss
	// TODO: Handle it
	if (hResult == DXGI_ERROR_DEVICE_REMOVED)
		LOG("The device was lost.");

	return hResult;
}

HRESULT CIDXGISwapChainHook::GetBuffer(UINT Buffer, REFIID riid, void **ppSurface)
{
	return m_pSwapChain->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT CIDXGISwapChainHook::SetFullscreenState(BOOL Fullscreen, IDXGIOutput *pTarget)
{
	return m_pSwapChain->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT CIDXGISwapChainHook::GetFullscreenState(BOOL *pFullscreen, IDXGIOutput **ppTarget)
{
	return m_pSwapChain->GetFullscreenState(pFullscreen, ppTarget);
}

HRESULT CIDXGISwapChainHook::GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc)
{
	return m_pSwapChain->GetDesc(pDesc);
}

HRESULT CIDXGISwapChainHook::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	return m_pSwapChain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT CIDXGISwapChainHook::ResizeTarget(const DXGI_MODE_DESC *pNewTargetParameters)
{
	return m_pSwapChain->ResizeTarget(pNewTargetParameters);
}

HRESULT CIDXGISwapChainHook::GetContainingOutput(IDXGIOutput **ppOutput)
{
	return m_pSwapChain->GetContainingOutput(ppOutput);
}

HRESULT CIDXGISwapChainHook::GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats)
{
	return m_pSwapChain->GetFrameStatistics(pStats);
}

HRESULT CIDXGISwapChainHook::GetLastPresentCount(UINT *pLastPresentCount)
{
	return m_pSwapChain->GetLastPresentCount(pLastPresentCount);
}