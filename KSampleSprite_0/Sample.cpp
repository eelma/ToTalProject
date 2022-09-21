#include "Sample.h"

bool	Sample::Init()
{
    I_Tex.SetDevice(m_pd3dDevice, m_pImmediateContext);
    I_Shader.SetDevice(m_pd3dDevice, m_pImmediateContext);
   
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


GAME_RUN(KSampleSprite_0, 1024, 768)
