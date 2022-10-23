#include "KGameCore.h"
bool		KGameCore::KCoreInit()
{
	KDevice::Init();
	KDxState::SetState(m_pd3dDevice.Get());
	I_Tex.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	I_Shader.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	I_Sound.Init();
	I_Input.Init();
	I_Timer.Init();
	m_Writer.Init();
	IDXGISurface1* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackBuffer);
	m_Writer.Set(pBackBuffer);
	pBackBuffer->Release();

    return Init();
}
bool		KGameCore::KCoreFrame()
{
	
	I_Input.Frame();
	I_Timer.Frame();
	I_Sound.Frame();
	m_Writer.Frame();
    return Frame();
}
bool		KGameCore::KCorePreRender()
{
	m_pImmediateContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDepthStencilView.Get());
	float color[4] = { 0.34324f,0.52342f,0.798320f,1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV.Get(), color);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->PSSetSamplers(0, 1, &KDxState::g_pDefaultSSWrap);
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->RSSetViewports(1 ,&m_vp);
	m_pImmediateContext->RSSetState(KDxState::g_pDefaultRSSolid);
	m_pImmediateContext->OMSetDepthStencilState(KDxState::g_pDefaultDepthStencil, 0xff);

    return true;
}
bool		KGameCore::KCoreRender()
{
	KCorePreRender();
	Render(); //디버그 렌더 화면에 뭔가 뿌리고 나서 마지막에 해주는게 좋다
	I_Input.Render();
	I_Timer.Render();
	m_Writer.m_szDefaultText = I_Timer.m_szTimer;
	m_Writer.Render();
		KCorePostRender();
    return true;
}
bool		KGameCore::KCorePostRender()
{
    m_pSwapChain->Present(0, 0);
    return true;
}
bool		KGameCore::KCoreRelease()
{
	Release();
	I_Input.Release();
	I_Timer.Release();
	m_Writer.Release();
	I_Sound.Release();
	KDxState::Release();
	KDevice::Release();
    return true;
}


bool        KGameCore::Run()
{
	KCoreInit();
	
	while (bGameRun)
	{
		if (KWindow::Run() == true)
		{
			KCoreFrame();
			KCoreRender();

		}
		else
		{
			bGameRun = false;
		}

	}

	KCoreRelease();
	
    return true;
}

HRESULT KGameCore::CreateDXResource()
{
	m_Writer.Init();
	IDXGISurface1* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackBuffer);
	m_Writer.Set(pBackBuffer);
	pBackBuffer ->Release();
	return S_OK;
}

HRESULT KGameCore::DeleteDXResource()
{
	m_Writer.DeleteDXResource();
	return E_NOTIMPL;
}
