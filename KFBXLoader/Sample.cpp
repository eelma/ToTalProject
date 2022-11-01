#include "Sample.h"
bool	Sample::Init()
{
	KFbxLoader* pFbxLoaderA = new KFbxLoader;
	if (pFbxLoaderA->Init())
	{
		pFbxLoaderA->Load("../../data/fbx/box.fbx");
	}
	m_fbxList.push_back(pFbxLoaderA);

	KFbxLoader* pFbxLoaderB = new KFbxLoader;
	if (pFbxLoaderB->Init())
	{
		pFbxLoaderB->Load("../../data/fbx/SM_Rock.fbx");
	}
	m_fbxList.push_back(pFbxLoaderB);

	W_STR szDefaultDir = L"../../data/fbx/";
	wstring shaderfilename = L"../../data/shader/DefaultObject.txt";
	for(auto fbx: m_fbxList)
	{
		for (int iObj = 0; iObj < fbx->m_pDrawObjList.size(); iObj++)
		{
			KBaseObject* pObj = fbx->m_pDrawObjList[iObj];
			wstring szLoad = szDefaultDir + pObj->m_szTextureName;
			pObj->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(),
				shaderfilename, szLoad);
		}
	}
	m_pMainCamera = new KCameraDebug;
	m_pMainCamera->CreateViewMatrix(KVector(50, 6, -50), KVector(0, 6, 0), KVector(0, 1, 0));
	m_pMainCamera->CreateProjMatrix(1.0f, 1000.0f, T_PI * 0.25f,
		(float)g_rtClient.right / (float)g_rtClient.bottom);
		
	return true;
}
bool	Sample::Frame()
{
	m_pMainCamera->Frame();
	for (auto fbx : m_fbxList)
	{
		fbx->Frame();
	}
	return true;
}
bool	Sample::Render()
{
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		m_pImmediateContext->RSSetState(KDxState::g_pDefaultRSWireFrame);
	}
	for(int iModel=0;iModel<m_fbxList.size();iModel++)
	{
		for (int iObj = 0; iObj < m_fbxList[iModel]->m_pDrawObjList.size(); iObj++)
		{
			KMatrix matWorld;
			matWorld._41 = 100 * iModel;
			m_fbxList[iModel]->m_pDrawObjList[iObj]->SetMatrix(&matWorld,
				&m_pMainCamera->m_matView,
				&m_pMainCamera->m_matProj);
			m_fbxList[iModel]->m_pDrawObjList[iObj]->Render();
		}
	}
	m_pImmediateContext->RSSetState(KDxState::g_pDefaultRSSolid);
	return true;
}
bool	Sample::Release()
{
	for (auto fbx : m_fbxList)
	{
		fbx->Release();
	}
	return true;
}
GAME_RUN(TFBXLoader, 800, 600)