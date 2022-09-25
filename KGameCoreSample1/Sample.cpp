#include "Sample.h"
bool Sample::Init()
{
	KDevice::Init();
	return true;
}

bool Sample::Frame()
{
	KDevice::Frame();
	return true;
}

bool Sample::Render()
{
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
	m_pSwapChain->Present(0, 0);
	
	return true;
}

bool Sample::Release()
{
	KDevice::Release();
	return true;
}

bool Sample::Run()
{
	Init();
	bool bGameRun = true;
	while (bGameRun)
	{
		if (KWindow::Run() == true)
		{
			Frame();
			Render();
			
		}
		else
		{
			bGameRun = false;
		}
		
	}
	
	Release();
	return true;
}

GAME_RUN(KGameCoreSample1, 800, 600)