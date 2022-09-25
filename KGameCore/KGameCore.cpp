#include "KGameCore.h"
bool		KGameCore::KCoreInit()
{
	KDevice::Init();
	I_Input.Init();
	I_Timer.Init();
    return Init();
}
bool		KGameCore::KCoreFrame()
{
	
	I_Input.Frame();
	I_Timer.Frame();
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
	Render(); //디버그 렌더 화면에 뭔가 뿌리고 나서 마지막에 해주는게 좋다
	I_Input.Render();
	I_Timer.Render();
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
