#include "Sample.h"


bool Sample::Init()
{
	m_pTitle = make_shared<KSceneTitle>();
	//m_pInGame = make_shared<KSceneInGame>();

	m_pTitle->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"");
	//m_pInGame->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"");
	m_pTitle->Init();
	//m_pInGame->Init();
	m_pCurrentScene = m_pTitle;

	m_Quadtree.Create(((KSceneTitle*)m_pCurrentScene.get())->m_pMainCamera,
						((KSceneTitle*)m_pCurrentScene.get())->m_pMap);

	wstring shaderfilename = L"DefaultShape.txt";
	m_DirLine.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), shaderfilename, L"../../data/gameHeight.png");
	m_DirLine.m_matWorld.Scale(1000.0f, 1000.0f, 1000.0f);


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

		m_pImmediateContext->OMSetDepthStencilState(KDxState::g_pDefaultDepthStencil, 0xff);
		KSceneTitle* pScene = (KSceneTitle*)m_pCurrentScene.get();
		pScene->m_pMap->SetMatrix(nullptr,
			&pScene->m_pMainCamera->m_matView,
			&pScene->m_pMainCamera->m_matProj);
		m_Quadtree.Frame();
		m_Quadtree.Render();

		m_pCurrentScene->Render();

		m_DirLine.SetMatrix(nullptr, &m_pCurrentScene->m_pMainCamera->m_matView, &m_pCurrentScene->m_pMainCamera->m_matProj);
		m_DirLine.Render();

	

	return true;
}
bool Sample::Release()
{
	m_DirLine.Release();
	m_pTitle->Release();
	//m_pInGame->Release();


	return true;
}

GAME_RUN(KSampleTexture, 800, 600)