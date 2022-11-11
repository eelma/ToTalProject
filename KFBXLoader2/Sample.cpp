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
	/*KFbxFile* pFbxLoaderC = new KFbxFile;
	if (pFbxLoaderC->Init())
	{
		pFbxLoaderC->Load("../../data/fbx/MultiCameras.fbx");
	}
	m_fbxList.push_back(pFbxLoaderC);*/

	KFbxFile* pFbxLoaderA = new KFbxFile;
	if (pFbxLoaderA->Init())
	{
		if (pFbxLoaderA->Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx"))
		{

			pFbxLoaderA->CreateConstantBuffer(m_pd3dDevice.Get());

		}
	}
	m_fbxList.push_back(pFbxLoaderA);

	/*KFbxFile* pFbxLoaderB = new KFbxFile;
	if (pFbxLoaderB->Init())
	{
		pFbxLoaderB->Load("../../data/fbx/SM_Rock.fbx");
	}
	m_fbxList.push_back(pFbxLoaderB);*/

	W_STR szDefaultDir = L"../../data/fbx/";
	wstring shaderfilename = L"SKinning.txt";
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
	m_pMainCamera->CreateViewMatrix(TVector3(0, 6, -50), TVector3(0, 0, 0), TVector3(0, 1, 0));
	m_pMainCamera->CreateProjMatrix(1.0f, 10000.0f, T_PI * 0.25f,
		(float)g_rtClient.right / (float)g_rtClient.bottom);
		
	return true;
}
bool	Sample::Frame()
{
	ClearD3D11DeviceContext(m_pImmediateContext.Get());
	m_pMainCamera->Frame();
	for (auto fbxfile : m_fbxList)
	{
		fbxfile->UpdateFrame(m_pImmediateContext.Get());
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
	//vLight=vLight*matRotation;
	D3DXVec3TransformCoord(&vLight, &vLight, &matRotation);
	D3DXVec3Normalize(&vLight,&vLight);

	for(int iFbxFile=0;iFbxFile<m_fbxList.size();iFbxFile++)
	{
		m_pImmediateContext->VSSetConstantBuffers(1, 1, &m_fbxList[iFbxFile]->m_pConstantBufferBone);
		for(int iObj=0;iObj<m_fbxList[iFbxFile]->m_pDrawObjList.size();iObj++)
		{
			KFbxObject* pObj = m_fbxList[iFbxFile]->m_pDrawObjList[iObj];
			TMatrix matControlWorld;
			D3DXMatrixRotationY(&matControlWorld, g_fGameTimer);
				pObj->m_cbData.x = vLight.x;
				pObj->m_cbData.y = vLight.y;
				pObj->m_cbData.z = vLight.z;
				pObj->SetMatrix(&matControlWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
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