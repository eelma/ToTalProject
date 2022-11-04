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
            return pNewData;
        }
    }
    delete pNewData;
    return nullptr;
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
W_STR KTextureManager::GetSplitName(wstring fullpath)
{
    W_STR name;
    TCHAR dirve[MAX_PATH] = { 0, };
    TCHAR dir[MAX_PATH] = { 0, };
    TCHAR filename[MAX_PATH] = { 0, };
    TCHAR ext[MAX_PATH] = { 0, };
    _tsplitpath_s(fullpath.c_str(),
        dirve, dir, filename, ext);
    name = filename;
    name += ext;
    return name;
}
W_STR KTextureManager::GetSplitName(string fullpath)
{
    W_STR szUnicode = to_mw(fullpath);
    W_STR name;
    TCHAR dirve[MAX_PATH] = { 0, };
    TCHAR dir[MAX_PATH] = { 0, };
    TCHAR filename[MAX_PATH] = { 0, };
    TCHAR ext[MAX_PATH] = { 0, };
    _tsplitpath_s(szUnicode.c_str(),
        dirve, dir, filename, ext);
    name = filename;
    name += ext;
    return name;
}
KTextureManager::KTextureManager()
{


}
KTextureManager::~KTextureManager()
{
    Release();
}
