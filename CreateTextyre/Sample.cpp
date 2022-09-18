#include "Sample.h"


bool Sample::Init()
{
    KDevice::Init();
    
    HRESULT  hr = DirectX::CreateWICTextureFromFile(
        m_pd3dDevice,
        m_lmmediateContext,
        L"../../data/kgcabk.bmp",
        &m_Texture,
        &m_pTextureSRV
    );
    //"kgcabk.bmp"
   
    return true;
}

bool Sample::Frame()
{
    KDevice::Frame();
    return true;
}

bool Sample::Render()
{

    KDevice::Render();
   
    return true;
}

bool Sample::Release()
{
    KDevice::Release();
    if (m_Texture)m_Texture->Release();
    if (m_pTextureSRV)m_pTextureSRV->Release();
    return true;
}


GAME_RUN(P2_CreateDeice_0,1024,768);
