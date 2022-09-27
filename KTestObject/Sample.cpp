#include "Sample.h"

bool Sample::Init()
{
	I_Shader.SetDevice(m_pd3dDevice, m_pImmediateContext);
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	KTexture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	m_pMap = new KMapObject;
	m_pMap->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/gameHeight.png");

	m_pUser = new KUser2D;
	m_pUser->Create(m_pd3dDevice, m_pImmediateContext,
		L"DefaultShapeMask.txt",
		L"../../data/bitmap1.bmp");
	m_pUser->SetMask(pMaskTex);
	m_pUser->m_fSpeed = 300.0f;
	m_pUser->SetRect({ 91,2,40,59 });
	m_pUser->SetPosition({ g_rtClient.right / 2.0f,g_rtClient.bottom - 100.0f });

	

	/*for (int iObj = 0; iObj < 1; iObj++)
	{
		KBaseObject* pObj = new KBaseObject;
		pObj->Create(m_pd3dDevice,
			m_pImmediateContext,
			shaderfilename,
			L"../../data/air.bmp"
			);
		m_ObjectList.push_back(pObj);
	}*/
	/*for (int iObj = 0; iObj < 10; iObj++)
	{
		KBaseObject* pObj = new KBaseObject;
		pObj->Create(m_pd3dDevice,
			m_pImmediateContext,
			L"../../data/shader/DefaultShape.txt",
			L"../../data/bitmap1.bmp"
			);
		m_ObjectList.push_back(pObj);
	}*/


	
	return true;
}
bool Sample::Frame()
{
	m_pMap->Frame();
	m_pUser->Frame();
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj]->Frame();
	}
	return true;
}
bool Sample::Render()
{
	m_pMap->Render();
	
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj]->Render();
	}
	m_pUser->PreRender();
	//1번 레지스터에 마스크 이미지를 넘길 수 있다
	m_pImmediateContext->PSSetShaderResources(1, 1, &m_pUser->m_pMaskTex->m_pTextureSRV);
	m_pUser->PostRender();
	return true;
}
bool Sample::Release()
{
	m_pMap->Release();
	m_pUser->Release();
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj]->Release();
		delete m_ObjectList[iObj];
	}
	/*for (int iObj = 0; iObj < m_ObjectTextureList.size(); iObj++)
	{
		m_ObjectTextureList[iObj]->Release();
		delete m_ObjectTextureList[iObj];
	}*/
	return true;
}

GAME_RUN(KTestTexture, 800, 600)