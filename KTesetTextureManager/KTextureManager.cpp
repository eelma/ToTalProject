#include "KTextureManager.h"
void KTextureManager::SetDevice(
    ID3D11Device* pd3dDevice,
    ID3D11DeviceContext* pContext)
{
    m_pd3dDevice = pd3dDevice;
    m_pImmediateContext = pContext;
}

KTexture* KTextureManager::Load(wstring name)
{
    HRESULT hr;
    //중복 제거
    auto data = Find(name);
    if (data != nullptr) return data;

    KTexture* pNewData = new KTexture;
    if (pNewData)
    {
        hr = pNewData->Load(m_pd3dDevice, m_pImmediateContext, name);
        if (SUCCEEDED(hr))
        {
            m_List.insert(make_pair(name,pNewData));
        }
    }
    return pNewData;
}
bool KTextureManager::Release()
{
    for (auto data : m_List)
    {
        KTexture* pTexture = data.second;
        if (pTexture)pTexture->Release();
        delete pTexture;
    }
    m_List.clear();
    return true;
}
KTexture* KTextureManager::Find(wstring name)
{

    auto iter = m_List.find(name);
    if (iter != m_List.end())
    {
        return iter->second;
    }
    return nullptr;

}
KTextureManager::KTextureManager()
{


}
KTextureManager::~KTextureManager()
{
    Release();
}
