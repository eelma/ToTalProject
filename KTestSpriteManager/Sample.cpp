#include "Sample.h"

bool Sample::Init()
{
	m_pTitle = new KSceneTitle;
	m_pInGame = new KScene;
	m_pTitle->Create(m_pd3dDevice, m_pImmediateContext, L"");
	m_pInGame->Create(m_pd3dDevice, m_pImmediateContext, L"");
	
	m_pTitle->Init();
	m_pInGame->Init();

	m_pCurrentScene = m_pTitle;
	//커렌트를 타이틀로하면 지형만 뿌려진다
	return true;
}
bool Sample::Frame()
{
	if (I_Input.GetKey(VK_F1) == KEY_PUSH)
	{
		m_pCurrentScene = m_pInGame;
	}
	m_pCurrentScene->Frame();
	return true;
}
bool Sample::Render()
{
	m_pCurrentScene->Render();
	return true;
}
bool Sample::Release()
{
	m_pTitle->Release();
	m_pInGame->Release();
	
	delete m_pTitle;
	delete m_pInGame;
	return true;
}

GAME_RUN(KTestTexture, 800, 600)