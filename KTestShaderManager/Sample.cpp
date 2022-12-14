#include "Sample.h"

HRESULT     KObject2D::CreateVertexShader(wstring filename)
{

	HRESULT hr = S_OK;
	if(m_pShader==nullptr)
	{
		m_pShader=I_Shader.Load(filename);
		if (m_pShader != nullptr & m_pShader->m_pVS != nullptr)
			{
			m_pVS = m_pShader->m_pVS;
			m_pVSCode = m_pShader->m_pVSCode;
			return S_OK;
			}
	}
	if (m_pShader != nullptr & m_pShader->m_pVS != nullptr)
	{
	m_pVS = m_pShader->m_pVS;
	m_pVSCode = m_pShader->m_pVSCode;
	return S_OK;

	}
	return E_FAIL;

}
HRESULT    KObject2D::CreatePixelShader(wstring filename)
{

	HRESULT hr = S_OK;
	if (m_pShader ==nullptr)
	{
		KShader* pShader = I_Shader.Load(filename);
		if(m_pShader != nullptr & m_pShader->m_pPS != nullptr)
		{
		m_pPS = m_pShader->m_pPS;
		m_pPSCode = m_pShader->m_pPSCode;
		return S_OK;
		}
	}
	if (m_pShader != nullptr & m_pShader->m_pPS != nullptr)
	{
		m_pPS = m_pShader->m_pPS;
		m_pPSCode = m_pShader->m_pPSCode;
		return S_OK;
	}
	
	return E_FAIL;

}

bool Sample::Init()
{
	I_Shader.SetDevice(m_pd3dDevice, m_pImmediateContext);
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";

	for (int iObj = 0; iObj < 10; iObj++)
	{
		KBaseObject* pObj = new KObject2D;
		pObj->Create(m_pd3dDevice,
			m_pImmediateContext,
			shaderfilename,
			L"../../data/kgcabk.bmp");
		m_ObjectList.push_back(pObj);
	}
	for (int iObj = 0; iObj < 10; iObj++)
	{
		KBaseObject* pObj = new KObject2D;
		pObj->Create(m_pd3dDevice,
			m_pImmediateContext,
			shaderfilename,
			L"../../data/bitmap1.bmp");
		m_ObjectList.push_back(pObj);
	}


	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;// 최근점 필터링
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	HRESULT hr = m_pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSS);
	return true;
}
bool Sample::Frame()
{
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj]->Frame();
	}
	return true;
}
bool Sample::Render()
{
	m_pImmediateContext->PSSetSamplers(0, 1, &g_pDefaultSS);
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj]->Render();
	}
	return true;
}
bool Sample::Release()
{
	g_pDefaultSS->Release();
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj]->Release();
		delete m_ObjectList[iObj];
	}
	for (int iObj = 0; iObj < m_ObjectTextureList.size(); iObj++)
	{
		m_ObjectTextureList[iObj]->Release();
		delete m_ObjectTextureList[iObj];
	}
	return true;
}

GAME_RUN(KTestTexture, 800, 600)