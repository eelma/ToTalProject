#include "KGameCore.h"
bool		KGameCore::KCoreInit()
{
	KDevice::Init();
	I_Tex.SetDevice(m_pd3dDevice, m_pImmediateContext);
	I_Shader.SetDevice(m_pd3dDevice, m_pImmediateContext);
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

	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);
	float color[4] = { 0.34324f,0.52342f,0.798320f,1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
	m_pImmediateContext->PSSetSamplers(0, 1, &KDxState::g_pDefaultSSWrap);
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
