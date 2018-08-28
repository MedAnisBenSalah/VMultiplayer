/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Direct3D11DeviceHook.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef DIRECT3D11DEVICEHOOK_H
#define DIRECT3D11DEVICEHOOK_H

class CDirect3D11DeviceHook //: public ID3D11Device
{
	public:
		CDirect3D11DeviceHook(ID3D11Device *pDevice);
		virtual ~CDirect3D11DeviceHook(void);

		// IUknown methods
		HRESULT __stdcall QueryInterface (REFIID riid, void** ppvObj);
		ULONG   __stdcall AddRef(void);
		ULONG   __stdcall Release(void);

		// ID3D11Device methods
		HRESULT __stdcall CreateBuffer(D3D11_BUFFER_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Buffer **ppBuffer);
		HRESULT __stdcall CreateTexture1D(D3D11_TEXTURE1D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture1D **ppTexture1D);
		HRESULT __stdcall CreateTexture2D(D3D11_TEXTURE1D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture2D **ppTexture2D);
		HRESULT __stdcall CreateTexture3D(D3D11_TEXTURE1D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture3D **ppTexture3D);
		HRESULT __stdcall CreateShaderResourceView(ID3D11Resource *pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc, ID3D11ShaderResourceView **ppView);
		HRESULT __stdcall CreateUnorderedAccessView(ID3D11Resource *pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc, ID3D11UnorderedAccessView **ppView);
		HRESULT __stdcall CreateRenderTargetView(ID3D11Resource *pResource, const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, ID3D11RenderTargetView **ppView);
		HRESULT __stdcall CreateDepthStencilView(ID3D11Resource *pResource, const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, ID3D11RenderTargetView **ppView);
 
	private:
	  ID3D11Device	*m_pDevice;
};

#endif 
