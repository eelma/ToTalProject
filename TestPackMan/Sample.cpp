#include "Sample.h"
#include"KWindow.h"
bool Sample::Init()
{
	m_pTitle = new KSceneTitle;
	m_pInGame = new KScene;
	m_pTitle->Create(m_pd3dDevice, m_pImmediateContext, L"");
	m_pInGame->Create(m_pd3dDevice, m_pImmediateContext, L"");

	m_pTitle->Init();
	m_pInGame->Init();
	m_pCurrentScene = m_pInGame;
	//m_pCurrentScene = m_pTitle;
	//커렌트를 타이틀로하면 지형만 뿌려진다

	m_pBGSound = I_Sound.GetPtr(L"PacMan1987.mp3");
	if (m_pBGSound == nullptr)
	{
		m_pBGSound = I_Sound.Load(L"../../data/sound/PacMan/PacMan1987.mp3");
	}
	m_move = I_Sound.GetPtr(L"pacman_chomp.wav");
	if (m_move == nullptr)
	{
		m_move = I_Sound.Load(L"../../data/sound/PacMan/pacman_chomp.wav");
	}
	m_pBGSound->Play(true);
	return true;
}
bool Sample::Frame()
{
	KeyDown();
	
	m_pCurrentScene->Frame();

	//I_Sound.Frame();
	
	return true;
}
bool Sample::Render()
{
	m_Writer.Render();
	
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
void Sample::KeyDown()
{
	if (I_Input.GetKey('T') == KEY_PUSH)
	{
		m_pCurrentScene = m_pInGame;
	}
	if (I_Input.GetKey(VK_INSERT) == KEY_PUSH)
	{
		m_pBGSound->VolumeUp();
	}
	if (I_Input.GetKey(VK_HOME) == KEY_PUSH)
	{
		m_pBGSound->VolumeDown();
	}
	if (I_Input.GetKey('W') == KEY_HOLD || I_Input.GetKey('A') == KEY_HOLD || I_Input.GetKey('S') == KEY_HOLD || I_Input.GetKey('D') == KEY_HOLD)
	{
		m_move->PlayEffect2();
	}
	if (I_Input.GetKey('Q') == KEY_PUSH)
	{
		m_pBGSound->Paused();
	}

}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR    lpCmdLine, int       nCmdShow)
{
 Sample demo;
 demo.SetWindow(hInstance,L"왜 안돼",800,1000);
 demo.Run(); return 1;

}
