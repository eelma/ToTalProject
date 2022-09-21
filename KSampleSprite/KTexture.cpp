#include "KTexture.h"
bool KTexture::Init()
{
    return true;
}
bool KTexture::Frame()
{
    return true;
}
bool KTexture::Render()
{
    return true;
}
bool KTexture::Release()
{
    if (m_Texture)m_Texture->Release();
    if (m_pTextureSRV)m_pTextureSRV->Release();
    m_Texture = nullptr;
    m_pTextureSRV = nullptr;
    return true;
}
HRESULT KTexture::Load(ID3D11Device* pd3dDevice,
    ID3D11DeviceContext* pImmediateContext,
         wstring filename)
{
    HRESULT  hr;
    m_pd3dDevice = pd3dDevice;
    m_pImmediateContext = pImmediateContext;
    hr = DirectX::CreateWICTextureFromFile(
        pd3dDevice,
        pImmediateContext,
        filename.c_str(),
        &m_Texture,
        &m_pTextureSRV);
    return hr;
}