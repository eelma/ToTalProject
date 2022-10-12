#include "KTexture.h"
<<<<<<< HEAD:GameCore/KTexture.cpp
HRESULT KTexture::Load(ID3D11Device* pd3dDevice,
=======
HRESULT KTexture::Load(ID3D11Device* pd3dDevice,// 디바이스 객체
>>>>>>> 48c3d63ff719d82e4eb39b8415a5f9bf170a0178:PacManCore/KTexture.cpp
	ID3D11DeviceContext* pImmediateContext, wstring name)
{
	HRESULT hr;
	
	hr=DirectX::CreateWICTextureFromFile(
		pd3dDevice,
		pImmediateContext,
		name.c_str(),
		(ID3D11Resource**)&m_pTexture,
		&m_pTextureSRV);
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(
			pd3dDevice,
			pImmediateContext,
			name.c_str(),
			(ID3D11Resource**)&m_pTexture,
			&m_pTextureSRV);
	}

	m_pTexture->GetDesc(&m_Desc);
	return hr;
}
void KTexture::Apply(ID3D11DeviceContext* pImmediateContext,
	UINT iSlot)
{
	pImmediateContext->PSSetShaderResources(iSlot, 1, &m_pTextureSRV);
}
bool KTexture::Release()
{
	if (m_pTexture)m_pTexture->Release();
	if (m_pTextureSRV)m_pTextureSRV->Release();
	return true;
}