#include "KScene.h"

bool		KScene::Create(
	ID3D11Device* pd3dDevice,// 디바이스 객체
	ID3D11DeviceContext* pImmediateContext,
	std::wstring shadername)
{


	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pImmediateContext;

	return true;
}

bool KScene::Init()
{
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	KTexture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	m_pMap = new KMapObject;
	m_pMap->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/gameHeight.png");

	m_pUser = new KUser2D;
	m_pUser->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/bitmap1.bmp");
	m_pUser->SetMask(pMaskTex);
	m_pUser->m_fSpeed = 300.0f;
	m_pUser->SetRect({ 91,2,40,59 });
	m_pUser->SetPosition({ g_rtClient.right / 2.0f,g_rtClient.bottom - 100.0f });

	for (int i = 0; i < 7; i++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/bitmap1.bmp"
		);
		if (i % 2 == 0)
		{
			npc->SetRect({ 46,62,68,79 });
		}
		else
		{
			npc->SetRect({ 115,62,37,35 });
		}
		npc->SetDirection({ randstep(-1.0f, 1.0f),randstep(-1.0f,1.0f) });
		npc->SetPosition({ 100.0f + i * 100.0f,100.0f });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}

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
bool KScene::Frame()
{
	m_pMap->Frame();
	m_pUser->Frame();
	for (int iObj = 0; iObj < m_pNpcList.size(); iObj++)
	{
		m_pNpcList[iObj]->Frame();
	}
	return true;
}
bool KScene::Render()
{
	m_pMap->Render();

	for (int iObj = 0; iObj < m_pNpcList.size(); iObj++)
	{
		m_pNpcList[iObj]->Render();
	}
	m_pUser->PreRender();
	//1번 레지스터에 마스크 이미지를 넘길 수 있다
	m_pImmediateContext->PSSetShaderResources(1, 1, &m_pUser->m_pMaskTex->m_pTextureSRV);
	m_pUser->PostRender();
	return true;
}
bool KScene::Release()
{
	m_pMap->Release();
	m_pUser->Release();
	for (int iObj = 0; iObj < m_pNpcList.size(); iObj++)
	{
		m_pNpcList[iObj]->Release();
		delete m_pNpcList[iObj];
	}
	/*for (int iObj = 0; iObj < m_ObjectTextureList.size(); iObj++)
	{
		m_ObjectTextureList[iObj]->Release();
		delete m_ObjectTextureList[iObj];
	}*/
	return true;
}
