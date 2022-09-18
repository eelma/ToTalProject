#include "Sample.h"
#include"KTextureManager.h"
bool	Sample::Init()
{
    I_Tex.SetDevice(m_pd3dDevice, m_pImmediateContext);
    for (int iobj = 0; iobj < 1; iobj++)
    {
        KBaseObject* pObject = new KBaseObject;
        pObject->Create(m_pd3dDevice, m_pImmediateContext,
            L"../../data/kgcabk.bmp",
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
    for (auto obj : m_pObjectList)
    {
        obj->Render();
    }
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
