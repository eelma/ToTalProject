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
    if (m_pTexture)m_pTexture->Release();
    if (m_pTextureSRV)m_pTextureSRV->Release();
    m_pTexture = nullptr;
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
        (ID3D11Resource**)&m_pTexture,//m_pTexture라는것을 얻어오게끔 돼있다
        &m_pTextureSRV);

    
    return hr;
}