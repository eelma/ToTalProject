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

	m_pBGSound = I_Sound.GetPtr(L"PacMan1987.mp3");
	if (m_pBGSound == nullptr)
	{
		m_pBGSound = I_Sound.Load(L"../../data/sound/PacMan/PacMan1987.mp3");
	}
	m_pShot = I_Sound.GetPtr(L"GunShot.mp3");
	if (m_pShot == nullptr)
	{
		m_pShot = I_Sound.Load(L"../../data/sound/GunShot.mp3");
	}
	m_pEffect = I_Sound.GetPtr(L"romance.mid");
	if (m_pEffect == nullptr)
	{
		m_pEffect = I_Sound.Load(L"../../data/sound/romance.mid");
	}
	m_pBGSound->Play(true);
	return true;
}
bool Sample::Frame()
{
	if (I_Input.GetKey(VK_F1) == KEY_PUSH)
	{
		m_pCurrentScene = m_pInGame;
	}
	m_pCurrentScene->Frame();

	//I_Sound.Frame();
	
	return true;
}
bool Sample::Render()
{
	m_pCurrentScene->Render();
	m_Writer.Draw(0, 100, m_pBGSound->m_szBuffer);

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

GAME_RUN(KTestTexture, 800, 1000)