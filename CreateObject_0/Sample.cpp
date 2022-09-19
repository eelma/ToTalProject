#include "Sample.h"
#include"KTextureManager.h"
#include"KShaderManager.h"
bool	Sample::Init()
{
    I_Tex.SetDevice(m_pd3dDevice, m_pImmediateContext);
    I_Shader.SetDevice(m_pd3dDevice, m_pImmediateContext);

    I_Tex.Load(L"../../data/0.bmp");
    I_Tex.Load(L"../../data/1.bmp");
    I_Tex.Load(L"../../data/2.bmp");
    I_Tex.Load(L"../../data/3.bmp");
    I_Tex.Load(L"../../data/4.bmp");
    I_Tex.Load(L"../../data/5.bmp");
    I_Tex.Load(L"../../data/6.bmp");
    I_Tex.Load(L"../../data/7.bmp");
    I_Tex.Load(L"../../data/8.bmp");
    I_Tex.Load(L"../../data/9.bmp");

    I_Tex.Load(L"../../data/sprite/shine0.bmp");
    I_Tex.Load(L"../../data/sprite/shine1.bmp");
    I_Tex.Load(L"../../data/sprite/shine2.bmp");
    I_Tex.Load(L"../../data/sprite/shine3.bmp");
    I_Tex.Load(L"../../data/sprite/shine4.bmp");
    I_Tex.Load(L"../../data/sprite/shine5.bmp");
    I_Tex.Load(L"../../data/sprite/shine6.bmp");
    I_Tex.Load(L"../../data/sprite/shine7.bmp");
    I_Tex.Load(L"../../data/sprite/shine8.bmp");
    I_Tex.Load(L"../../data/sprite/shine9.bmp");
    
    for (int iobj = 0; iobj < 10; iobj++)
    {
        KBaseObject* pObject = new KBaseObject;
        pObject->Create(m_pd3dDevice, m_pImmediateContext,
            L"../../data/KGCABK.bmp",
            L"../../data/shader/DefaultShape.txt");
        m_pObjectList.push_back(pObject);
    }
    return true;
}
bool		Sample::Frame()
{
    for (auto obj : m_pObjectList)
    {
        obj->Frame();
    }
        return true;
}
bool		Sample::Render()
{
    /*
    for (auto obj : m_pObjectList)
    {
        obj->Render();
    }*/
    static float fTime = 0.0f;
    fTime += m_fElapseTimer;
    if (fTime >= 0.1f)
    {
        m_iTexIndex++;
        if (m_iTexIndex >= 10)m_iTexIndex = 0;
        fTime = fTime - 0.01f;
    }
    wstring name = L"../../data/sprite/shine";
    name += to_wstring(m_iTexIndex);
    name += L".bmp";
    m_pObjectList[0]->m_pTexture = I_Tex.Find(name);
    m_pObjectList[0]->Render();
    return true;
}
bool		Sample::Release()
{
    for (auto obj : m_pObjectList)
    {
        obj->Release();
        delete obj;
    }
    return true;
}


GAME_RUN(CreateObject_0, 1024, 768)
