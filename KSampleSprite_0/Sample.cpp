#include "Sample.h"

void KUser2D::SetRect(KRect rt)
{
    m_rt = rt;
}
//vPos(화면 좌표)를 ndc 좌표로 변경(컨버팅)해야한다
//화면 좌표로 세팅하고 내부적으로 ndc로 랜더링을한다
//ndc좌표를 만들어주는 기능이 필요하다
void KUser2D::SetPosition(KVector2D vPos)
{
    KVector2D pos = vPos;
    //0~800 -> 0~1-> -1~+1
    pos.x = (vPos.x / g_rtClient.right)*2.0f-1.0f;
    pos.y = (vPos.y / g_rtClient.bottom) * 2.0f - 1.0f;
}


bool	Sample::Init()
{
    
   
    //map
    /*KBaseObject* pObjectMap = new KBaseObject;    
    pObjectMap->Create(m_pd3dDevice, m_pImmediateContext,    
        L"../../data/KGCABK.bmp",    
        L"../../data/shader/DefaultShape.txt");    
    m_pObjectList.push_back(pObjectMap);*/


    //user character
    //{90,1,40,60} player 이미지 영역,{400,300}화면 스크린 좌표 버텍스 버퍼가 만들어져야한다
    //-1~+1에 대한 결과가 만들어진다
    //create 하면 -1~1의 버텍스 버퍼가 만들어진다 그 다음에 오브젝트에 푸쉬백
    m_pUser = new KUser2D;
    m_pUser->Create(m_pd3dDevice, m_pImmediateContext,
        L"../../data/bitmap1.bmp",
        L"../../data/shader/DefaultShape.txt");
    m_pUser->SetRect({ 90,1,40,60 });
    m_pUser->SetPosition({ (float)g_rtClient.right/2,(float)g_rtClient.bottom/2 });


    
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
