#include "KGameCore.h"
bool		KGameCore::KCoreInit()
{
    HRESULT hr;
    if (KDevice::Init() == false)
    {
        return false;
    }
    I_Tex.SetDevice(m_pd3dDevice, m_pImmediateContext);
    I_Shader.SetDevice(m_pd3dDevice, m_pImmediateContext);
    KDxState::SetState(m_pd3dDevice);
    I_Timer.Init();
    I_Input.Init();
    m_Writer.Init();
    
    m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&m_pBackBuffer);
    m_Writer.Set(m_pBackBuffer);

    return Init();
}
bool		KGameCore::KCoreFrame()
{
    I_Timer.Frame();
    I_Input.Frame();
    m_Writer.Frame();
    return Frame();
}
bool		KGameCore::KCorePreRender()
{
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);
    float color[4] = { 1.0f,1.0f,1.0f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
    //샘플러 스테이트 설정
    //g_pDefaultSS에 세팅된 세팅값이 픽셀셰이더 0번 슬롯에 넘어간다
    m_pImmediateContext->PSSetSamplers(0,1,&KDxState::g_pDefaultSS);
    return true;
}
bool		KGameCore::KCoreRender()
{

    KCorePreRender();
    Render();
    I_Timer.Render();
    I_Input.Render();
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
    m_pBackBuffer->Release();
    KDxState::Release();
    Release();
    I_Timer.Release();
    I_Input.Release();
    KDevice::Release();
    return true;
}


bool        KGameCore::Run()
{
    if (KCoreInit() == false)
    {
        KCoreRelease();
        return false;
    }
    MSG msg = { 0, };
    m_bGameRun = true;
    //게임의 로직을 돌리는 부분
    while (m_bGameRun)
    {
        //윈도우의 메세지 디스패쳐
        if (KWindow::Run() == false)
        {

            m_bGameRun = false;

        }
        else
        {
            if (!KCoreFrame() || !KCoreRender())
            {
             m_bGameRun = false;
            }
        }
    }

    KCoreRelease();

    return true;
}
