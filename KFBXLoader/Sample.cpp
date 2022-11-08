#include "Sample.h"
void Sample::ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext)
{
	//Unbind all objects from the immediate context
	if (pd3dDeviceContext == NULL)return;

	ID3D11ShaderResourceView* pSRVs[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	ID3D11RenderTargetView* pRTVs[16]= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	ID3D11DepthStencilView* pDSV = NULL;
	ID3D11Buffer* pBufers[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	ID3D11SamplerState* pSamplers[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };;
	UINT StrideOffset[16]= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	pd3dDeviceContext->VSSetShaderResources(0,16,pSRVs);
	pd3dDeviceContext->PSSetShaderResources(0,16,pSRVs);
}

bool	Sample::Init()
{
	/*KFbxLoader* pFbxLoaderC = new KFbxLoader;
	if (pFbxLoaderC->Init())
	{
		pFbxLoaderC->Load("../../data/fbx/MultiCameras.fbx");
	}
	m_fbxList.push_back(pFbxLoaderC);*/

	KFbxLoader* pFbxLoaderA = new KFbxLoader;
	if (pFbxLoaderA->Init())
	{
		pFbxLoaderA->Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx");
	}
	m_fbxList.push_back(pFbxLoaderA);

	/*KFbxLoader* pFbxLoaderB = new KFbxLoader;
	if (pFbxLoaderB->Init())
	{
		pFbxLoaderB->Load("../../data/fbx/SM_Rock.fbx");
	}
	m_fbxList.push_back(pFbxLoaderB);*/

	W_STR szDefaultDir = L"../../data/fbx/";
	wstring shaderfilename = L"../../data/shader/DefaultObject.txt";
	for(auto fbx: m_fbxList)
	{
		for (int iObj = 0; iObj < fbx->m_pDrawObjList.size(); iObj++)
		{
			KFbxObject* pObj = fbx->m_pDrawObjList[iObj];
			wstring szLoad = szDefaultDir + pObj->m_szTextureName;
			pObj->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), shaderfilename, szLoad);
		}
			
	}
	m_pMainCamera = new KCameraDebug;
	m_pMainCamera->CreateViewMatrix(TVector3(50, 6, -50), TVector3(0, 6, 0), TVector3(0, 1, 0));
	m_pMainCamera->CreateProjMatrix(1.0f, 1000.0f, T_PI * 0.25f,
		(float)g_rtClient.right / (float)g_rtClient.bottom);
		
	return true;
}
bool	Sample::Frame()
{
	ClearD3D11DeviceContext(m_pImmediateContext.Get());
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
	TVector3 vLight(0, 0, 1);
	TMatrix matRotation;
	D3DXMatrixRotationY(&matRotation, g_fGameTimer);
	D3DXVec3Normalize(&vLight,&vLight);

	for(int iModel=0;iModel<m_fbxList.size();iModel++)
	{
		for (int iObj = 0; iObj < m_fbxList[iModel]->m_pDrawObjList.size(); iObj++)
		{
			KFbxObject* pObj = m_fbxList[iModel]->m_pDrawObjList[iObj];
			
			pObj->m_fAnimFrame = pObj->m_fAnimFrame + g_fSecondPerFrame * pObj->m_fAnimSpeed * 30.0f * pObj->m_fAnimInverse;
			if (pObj->m_fAnimFrame > 50 || pObj->m_fAnimFrame < 0)
			{
				pObj->m_fAnimFrame = min(pObj->m_fAnimFrame, 50);
				pObj->m_fAnimFrame = max(pObj->m_fAnimFrame, 0);
				pObj->m_fAnimInverse *= -1.0f;
			}

			TMatrix matWorld = pObj->m_AnimTracks[pObj->m_fAnimFrame].matAnim;
				pObj->m_cbData.x = vLight.x;
				pObj->m_cbData.y = vLight.y;
				pObj->m_cbData.z = vLight.z;
				pObj->SetMatrix(&matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
				pObj->Render();
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