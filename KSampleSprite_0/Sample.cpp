#include "Sample.h"
void KUser2D::UpdateVertexBuffer()
{
    m_VertexList[0].p = { m_vPos.x, m_vPos.y,  0.0f };
    m_VertexList[0].t = { m_rtUV.x1,m_rtUV.y1 };

    m_VertexList[1].p = { m_vPos.x+m_vSize.x, m_vPos.y,  0.0f };
    m_VertexList[1].t = { m_rtUV.x1+m_rtUV.w,m_rtUV.y1 };

    m_VertexList[2].p = { m_vPos.x, m_vPos.y-m_vSize.y, 0.0f };
    m_VertexList[2].t = { m_rtUV.x1,m_rtUV.y1+m_rtUV.h };

    m_VertexList[3].p = m_VertexList[2].p;
    m_VertexList[3].t = m_VertexList[2].t;

    m_VertexList[4].p = m_VertexList[1].p;
    m_VertexList[4].t = m_VertexList[1].t;

    m_VertexList[5].p = { m_vPos.x+m_vSize.x, m_vPos.y - m_vSize.y, 0.0f };
    m_VertexList[5].t = { m_rtUV.x1+m_rtUV.w,m_rtUV.y1 + m_rtUV.h };

    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, NULL, NULL,&m_VertexList.at(0), 0, 0);
}
void KUser2D::SetRect(KRect rt)
{
    m_rtInit = rt;
    //image w,h
    //사실상 정점에 들어가는 uv값
    m_rtUV.x1 = rt.x1 / 400.0f;//u
    //1
    m_rtUV.y1 = rt.y1 / 300.0f;//v
    //40
    m_rtUV.w = rt.w / 400.0f;
    //60
    m_rtUV.h = rt.h/300.0f;
    
}
//vPos(화면 좌표)를 ndc 좌표로 변경(컨버팅)해야한다
//화면 좌표로 세팅하고 내부적으로 ndc로 랜더링을한다
//ndc좌표를 만들어주는 기능이 필요하다
void KUser2D::SetPosition(KVector2D vPos)
{
    //0~800 -> 0~1-> -1~+1
    m_vPos.x = (vPos.x / g_rtClient.right)*2.0f-1.0f;
    m_vPos.y = -((vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
    m_vSize.x = (m_rtInit.w / g_rtClient.right)*2;
    m_vSize.y = ((m_rtInit.h / g_rtClient.bottom))*2;
    UpdateVertexBuffer();
}


bool	Sample::Init()
{
    
   
    //map
    KBaseObject* pObjectMap = new KBaseObject;    
    pObjectMap->Create(m_pd3dDevice, m_pImmediateContext,    
        L"../../data/KGCABK.bmp",    
        L"../../data/shader/DefaultShape.txt");    
    m_pObjectList.push_back(pObjectMap);


    //user character
    //{90,1,40,60} player 이미지 영역,{400,300}화면 스크린 좌표 버텍스 버퍼가 만들어져야한다
    //-1~+1에 대한 결과가 만들어진다
    //create 하면 -1~1의 버텍스 버퍼가 만들어진다 그 다음에 오브젝트에 푸쉬백
    m_pUser = new KUser2D;
    m_pUser->Create(m_pd3dDevice, m_pImmediateContext,
        L"../../data/bitmap1.bmp",
        L"../../data/shader/DefaultShape.txt");
    m_pUser->SetRect({ 90,1,40,60 });
    m_pUser->SetPosition({ g_rtClient.right/2.0f,g_rtClient.bottom/ 2.0f });


    
    return true;
}
bool		Sample::Frame()
{
    for (auto obj : m_pObjectList)
    {
        obj->Frame();
    }
    m_pUser->Frame();
    return true;
}
bool		Sample::Render()
{
    
    for (auto obj : m_pObjectList)
    {
        obj->Render();
        
    }
    m_pUser->Render();
   
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


GAME_RUN(KSampleSprite_0, 800, 600)
