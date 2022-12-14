#include "KSceneTitle.h"
#include "KInput.h"
#include"KDxState.h"
bool       KSceneTitle::IsNextScene()
{
	return false;
}
bool KSceneTitle::Init()
{
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	m_pBG = new KBaseObject;
	m_pBG->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/KGCABK.bmp");

	m_pMap = new KMap;
	//2*n??+1
	m_pMap->Build(256 + 1, 256 + 1);
	m_pMap->Create(m_pd3dDevice, m_pImmediateContext, L"DefaultObject.txt", L"../../data/map/038.bmp");

	m_pBoxObj = new KObjectBox;
	m_pBoxObj->Create(m_pd3dDevice, m_pImmediateContext, L"DefaultObject.txt", L"../../data/box.jpg");
	m_pBoxObj->m_matWorld.Translation(0, 5, 0);

	m_pMainCamera = new KCameraDebug;
	m_pMainCamera->CreateViewMatrix(KVector(0, 30, -30), KVector(0, 0, 0), KVector(0, 1, 0));
	m_pMainCamera->CreateProjMatrix(1.0f, 1000.0f, T_PI * 0.25f,
		(float)g_rtClient.right / (float)g_rtClient.bottom);


	return true;
}
bool KSceneTitle::Frame()
{
	if (I_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
	{
		m_pMainCamera->m_fYaw += I_Input.m_ptOffset.x * 0.002f;
		m_pMainCamera->m_fPitch += I_Input.m_ptOffset.y * 0.002f;
	}
	m_pMainCamera->Frame();
	m_pBoxObj->Frame();
	/*m_pBoxObj->m_matWorld.RotationY(g_fGameTimer);
	m_pBoxObj->m_matWorld._41 = m_pBoxObj->m_vPos.x;
	m_pBoxObj->m_matWorld._42 = m_pBoxObj->m_vPos.y;
	m_pBoxObj->m_matWorld._43 = m_pBoxObj->m_vPos.z;*/

	return true;
}
bool KSceneTitle::Render()
{
	/*m_pImmediateContext->OMSetDepthStencilState(KDxState::g_pDefaultDepthStencil, 0xff);
	m_pMap->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pMap->UpdateBuffer((KCameraDebug*)m_pMainCamera);
	m_pMap->Render();*/
		KCameraDebug* pDCam = (KCameraDebug*)m_pMainCamera;
	bool bRender = pDCam->m_vFrustum.ClassifyPoint(m_pBoxObj->m_vPos);
	if (bRender)
	{
		m_pBoxObj->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		m_pBoxObj->Render();
	}

	//m_pBG->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	//m_pBG->Render();
	return true;
}
bool KSceneTitle::Release()
{
	m_pBoxObj->Release();
	delete m_pBoxObj;

	m_pBG->Release();

	m_pMap->Release();
	delete m_pMap;
	return true;
}