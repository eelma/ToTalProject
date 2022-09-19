#include "KGameCore.h"
bool		KGameCore::KCoreInit()
{
    HRESULT hr;
    if (KDevice::Init() == false)
    {
        return false;
    }
        return Init();
}
bool		KGameCore::KCoreFrame()
{
    m_Timer.Frame();

    return Frame();
}
bool		KGameCore::KCorePreRender()
{
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);
    float color[4] = { 1.0f,1.0f,1.0f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
    return true;
}
bool		KGameCore::KCoreRender()
{
    KCorePreRender();
    Render();
    m_Timer.Render();
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
    m_Timer.Release();
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

   
    

    while (m_bGameRun)
    {
        if (WM_QUIT == msg.message)
        {
            break;
        }
        // 장점 : 메세지큐에 메세지가 없어도 반환됨.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // 메세지 번역
            DispatchMessage(&msg);  // 메세지 프로시져에 전달한다.
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
