#include "Sample.h"


bool Sample::Init()
{
	

	m_pTitle = make_shared<KSceneTitle>();
	m_pInGame = make_shared<KSceneInGame>();
	
	m_pTitle->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"");
	m_pInGame->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"");
	m_pTitle->Init();
	m_pInGame->Init();
	m_pCurrentScene = m_pTitle;

	return true;
}
bool Sample::Frame()
{
	if (m_pCurrentScene->IsNextScene())
	{
		m_pCurrentScene = m_pInGame;
	}
	m_pCurrentScene->Frame();
	return true;
}
bool Sample::Render()
{
	
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		m_pImmediateContext->RSSetState(KDxState::g_pDefaultRSWireFrame);
	}
	
	m_pCurrentScene->Render();
	return true;
}
bool Sample::Release()
{
	m_pTitle->Release();
	m_pInGame->Release();

	
	return true;
}

GAME_RUN(KSampleTexture, 800, 600)