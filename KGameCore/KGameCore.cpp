#include "KGameCore.h"
bool		KGameCore::KCoreInit()
{
	KDevice::Init();
   
    return Init();
}
bool		KGameCore::KCoreFrame()
{
	KDevice::Frame();
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
