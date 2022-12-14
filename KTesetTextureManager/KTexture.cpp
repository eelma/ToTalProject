#include "KTexture.h"
bool KTexture::Load(ID3D11Device* pd3dDevice,// ?????̽? ??ü
	ID3D11DeviceContext* pImmediateContext, std::wstring name)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(
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
	return true;
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