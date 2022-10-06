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
	KTexture* pMaskTex = I_Tex.Load(L"../../data/PacManmask.bmp");

	m_pMap = new KMapObject;
	m_pMap->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/PacMan_Map.png");

	m_pUser = new KUser2D;
	m_pUser->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/PacMan.png");
	m_pUser->SetMask(pMaskTex);
	m_pUser->m_fSpeed = 300.0f;
	m_pUser->SetRect({ 111,53,30,31 });
	m_pUser->SetPosition({ g_rtClient.right / 2.0f,g_rtClient.bottom - 100.0f });

	InitNPC();
	InitMapObj();


	return true;
}
bool KScene::Frame()
{
	//m_pMap->Frame();
	static KVector2D vSize = { 800,800 };
	for (auto iter = m_pNpcList.begin(); iter != m_pNpcList.end(); iter++)
	{
		KNpc2D* npc = *iter;
		npc->SetCameraSize(vSize);
		npc->SetCameraPos(m_vCamera);
		npc->Frame();
	}

	for (auto nono = m_StaticList.begin(); nono != m_StaticList.end();)
	{
		if (KCollision::RectToRect((*nono)->m_rtCollision, m_pUser->m_rtCollision))
		{
			if (m_pUser->m_rtCollision.y1 <= ((*nono)->m_rtCollision.y1 + (*nono)->m_rtCollision.h)&& (m_pUser->m_rtCollision.y1 + m_pUser->m_rtCollision.h)>((*nono)->m_rtCollision.y1 + (*nono)->m_rtCollision.h))
			{
				if ((m_pUser->m_rtCollision.x1 + m_pUser->m_rtCollision.w) < ((*nono)->m_rtCollision.x1 + (*nono)->m_rtCollision.w))
				{
					if ((m_pUser->m_rtCollision.x1) > ((*nono)->m_rtCollision.x1))
					{

						m_pUser->m_vPos.y = (*nono)->m_rtCollision.y1 + (*nono)->m_rtCollision.h + 20.0f;
						m_pUser->Frame();
						continue;
					}
				}
			}else
			if ((m_pUser->m_rtCollision.y1+ m_pUser->m_rtCollision.h) >= (*nono)->m_rtCollision.y1)
			{
				if ((m_pUser->m_rtCollision.x1 + m_pUser->m_rtCollision.w) < ((*nono)->m_rtCollision.x1 + (*nono)->m_rtCollision.w))
				{
					if ((m_pUser->m_rtCollision.x1) > ((*nono)->m_rtCollision.x1))
					{

						m_pUser->m_vPos.y = (*nono)->m_rtCollision.y1 - 20.0f;
						m_pUser->Frame();
						continue;
					}
				}
				
			}
			if ((m_pUser->m_rtCollision.x1 + m_pUser->m_rtCollision.w) >= ((*nono)->m_rtCollision.x1)&& (m_pUser->m_rtCollision.x1 + m_pUser->m_rtCollision.w) <= ((*nono)->m_rtCollision.x1 + (*nono)->m_rtCollision.w))
			{
				m_pUser->m_vPos.x = (*nono)->m_rtCollision.x1- 20.0f;
				m_pUser->Frame();
				continue;
			}else
			if ((m_pUser->m_rtCollision.x1) <= ((*nono)->m_rtCollision.x1 + (*nono)->m_rtCollision.w)&&(m_pUser->m_rtCollision.x1+m_pUser->m_rtCollision.w)> ((*nono)->m_rtCollision.x1 + (*nono)->m_rtCollision.w))
			{
				m_pUser->m_vPos.x = (*nono)->m_rtCollision.x1 + (*nono)->m_rtCollision.w + 20.0f;
				m_pUser->Frame();
				continue;
			}
			
			
		}
			
		else nono++;
	}

	for (auto src = m_pNpcList.begin(); src != m_pNpcList.end();)
	{
		if (KCollision::RectToRect((*src)->m_rtCollision, m_pUser->m_rtCollision))
		{
			score += 200.0f;
			delete* src;
			src = m_pNpcList.erase(src);
			if (score == 1000)
			{
				
				/*if (MessageBox(g_hWnd, L"뻥이지롱", L"게임끝", MB_OK) == IDOK)
				{
					DestroyWindow(g_hWnd);
				}*/
				

			}
			continue;
		}
		else src++;
	}
	
	m_pUser->Frame();
	for (auto data: m_pNpcList)
	{
		data->Frame();
	}
	for (auto data : m_StaticList)
	{
		data->Frame();
	}
	
	return true;
}
bool KScene::Render()
{
	m_pMap->Render();

	for (auto data : m_pNpcList)
	{
		data->Render();
	}
	for (auto data : m_StaticList)
	{
		data->Render();
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
	for (auto data : m_pNpcList)
	{
		data->Release();
		delete data;
	}
	for (auto data : m_StaticList)
	{
		data->Release();
		delete data;
	}
	/*for (int iObj = 0; iObj < m_ObjectTextureList.size(); iObj++)
	{
		m_ObjectTextureList[iObj]->Release();
		delete m_ObjectTextureList[iObj];
	}*/
	return true;
}


void KScene::InitNPC()
{
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	KTexture* pMaskTex = I_Tex.Load(L"../../data/PacManmask.bmp");


	for (int iNpc = 0; iNpc < 8; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ 50,(float)50+iNpc*30 });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}
	for (int iNpc = 0; iNpc < 11; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ (float)50 + iNpc * 30 ,50});
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}
	for (int iNpc = 0; iNpc < 5; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ 350 ,(float)50 + iNpc * 30 });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}
	for (int iNpc = 0; iNpc < 28; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ 200 ,(float)50 + iNpc * 30 });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}
	for (int iNpc = 0; iNpc < 9; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ (float)80 + iNpc * 30 ,170 });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}

	for (int iNpc = 0; iNpc < 4; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ (float)80 + iNpc * 30 ,260 });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}
	for (int iNpc = 0; iNpc < 6; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ (float)50 + iNpc * 30 ,860 });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}
	for (int iNpc = 0; iNpc < 6; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ (float)50 + iNpc * 30 ,650 });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}

	for (int iNpc = 0; iNpc < 5; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ 50 ,650 + (float)iNpc * 30 });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}
	KNpc2D* npc1 = new KNpc2D;
	npc1->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/PacMan.png");
	npc1->SetRect({ 268,108,16,16 });
	npc1->SetPosition({ 80 ,750 });
	npc1->SetMask(pMaskTex);
	m_pNpcList.push_back(npc1);
	for (int iNpc = 0; iNpc < 4; iNpc++)
	{
		KNpc2D* npc = new KNpc2D;
		npc->Create(m_pd3dDevice, m_pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/PacMan.png");
		npc->SetRect({ 268,108,16,16 });
		npc->SetPosition({ 110 ,(float)750+iNpc*30 });
		npc->SetMask(pMaskTex);
		m_pNpcList.push_back(npc);
	}
	
}
void KScene::InitMapObj()
{
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	KTexture* statictex = I_Tex.Load(L"../../data/whitemask.png");

	KStaticObject* stac = new KStaticObject;
	stac->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/white.png");
	stac->SetRect({ 0,0,40,400 });
	stac->SetPosition({ 5 , 150 });
	stac->SetMask(statictex);
	m_StaticList.push_back(stac);

	KStaticObject* stac1 = new KStaticObject;
	stac1->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/white.png");
	stac1->SetRect({ 0,100,800,20 });
	stac1->SetPosition({ 400 , 5 });
	stac1->SetMask(statictex);
	m_StaticList.push_back(stac1);

	KStaticObject* stac2 = new KStaticObject;
	stac2->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/white.png");
	stac2->SetRect({ 50,150,200,130 });
	stac2->SetPosition({ 400 , 465 });
	stac2->SetMask(statictex);
	m_StaticList.push_back(stac2);

	KStaticObject* stac3 = new KStaticObject;
	stac3->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/white.png");
	stac3->SetRect({ 0,0,120,130 });
	stac3->SetPosition({ 80 , 370 });
	stac3->SetMask(statictex);
	m_StaticList.push_back(stac3);

	KStaticObject* stac4 = new KStaticObject;
	stac4->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/white.png");
	stac4->SetRect({ 0,0,30,150 });
	stac4->SetPosition({ 400 , 60 });
	stac4->SetMask(statictex);
	m_StaticList.push_back(stac4);

}
