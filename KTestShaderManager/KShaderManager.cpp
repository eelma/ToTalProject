#include "KShaderManager.h"
void KShaderManager::SetDevice(
    ID3D11Device* pd3dDevice,
    ID3D11DeviceContext* pContext)
{
    m_pd3dDevice = pd3dDevice;
    m_pImmediateContext = pContext;
}

KShader* KShaderManager::Load(wstring name)
{
    HRESULT hr;
    //중복 제거
  auto iter= m_List.find(name);
  if (iter != m_List.end())
  {
      return iter->second;
  }

  KShader* pNewData = new KShader;
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
KShader* KShaderManager::VLoad(wstring name, string funName)
{
    HRESULT hr;
    //중복 제거
    wstring vName = name;
    vName += mtw(funName);
    auto iter = m_List.find(vName);
    if (iter != m_List.end())
    {
        return iter->second;
    }

    KShader* pNewData = new KShader;
   
    if (pNewData)
    {
        hr = pNewData->Load(m_pd3dDevice, m_pImmediateContext, name);
        if (SUCCEEDED(hr))
        {
            m_List.insert(make_pair(name, pNewData));
        }
    }
    return pNewData;
};
KShader* KShaderManager::PLoad(wstring name, string funName)
{
    HRESULT hr;
    //중복 제거
    wstring vName = name;
    vName += mtw(funName);
    auto iter = m_List.find(vName);
    if (iter != m_List.end())
    {
        return iter->second;
    }

    KShader* pNewData = new KShader;

    if (pNewData)
    {
        hr = pNewData->Load(m_pd3dDevice, m_pImmediateContext, name);
        if (SUCCEEDED(hr))
        {
            m_List.insert(make_pair(name, pNewData));
        }
    }
    return pNewData;
};

bool KShaderManager::Release()
{
    for (auto data : m_List)
    {
        KShader* pData = data.second;
        if (pData)pData->Release();
        delete pData;
    }
    m_List.clear();
    return true;
}

KShaderManager::KShaderManager()
{


}
KShaderManager::~KShaderManager()
{
   
    Release();
}
