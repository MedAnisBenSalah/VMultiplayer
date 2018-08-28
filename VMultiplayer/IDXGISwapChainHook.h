/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: IDXGISwapChainHook.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef IDXGISWAPCHAINHOOK_H
#define IDXGISWAPCHAINHOOK_H

class CIDXGISwapChainHook : public IDXGISwapChain
{
	public:
		CIDXGISwapChainHook(IDXGISwapChain *pSwapChain, ID3D11Device *pDevice, ID3D11DeviceContext *pContext);
		virtual ~CIDXGISwapChainHook(void);

		// IUknown methods
		HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObj);
		ULONG   __stdcall AddRef(void);
		ULONG   __stdcall Release(void);
		
		// IDXGIObject methods
		HRESULT __stdcall SetPrivateData(REFGUID Name, UINT DataSize, const void *pData);
		HRESULT __stdcall SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown);
		HRESULT __stdcall GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData);
		HRESULT __stdcall GetParent(REFIID riid, void **ppParent);
		
		// IDXGIDeviceSubObject methods
		HRESULT __stdcall GetDevice(REFIID riid, void **ppDevice);

		// IDXGISwapChain methods
		HRESULT __stdcall Present(UINT SyncInterval, UINT Flags);
		HRESULT __stdcall GetBuffer(UINT Buffer, REFIID riid, void **ppSurface);
		HRESULT __stdcall SetFullscreenState(BOOL Fullscreen, IDXGIOutput *pTarget);
		HRESULT __stdcall GetFullscreenState(BOOL *pFullscreen, IDXGIOutput **ppTarget);
		HRESULT __stdcall GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc);
		HRESULT __stdcall ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
		HRESULT __stdcall ResizeTarget(const DXGI_MODE_DESC *pNewTargetParameters);
		HRESULT __stdcall GetContainingOutput(IDXGIOutput **ppOutput);
		HRESULT __stdcall GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats);
		HRESULT __stdcall GetLastPresentCount(UINT *pLastPresentCount);
 
	private:
		IDXGISwapChain			*m_pSwapChain;
		ID3D11Device			*m_pDevice;
		ID3D11DeviceContext		*m_pDeviceContext;
};

#endif 
