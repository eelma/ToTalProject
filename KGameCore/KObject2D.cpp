#include "KObject2D.h"
#include"KTextureManager.h"
void KObject2D::UpdateVertexBuffer()
{
    m_VertexList[0].p = { m_vDrawPos.x, m_vDrawPos.y,  0.0f };
    m_VertexList[0].t = { m_rtUV.x1,m_rtUV.y1 };

    m_VertexList[1].p = { m_vDrawPos.x + m_vDrawSize.x, m_vDrawPos.y,  0.0f };
    m_VertexList[1].t = { m_rtUV.x1 + m_rtUV.w,m_rtUV.y1 };

    m_VertexList[2].p = { m_vDrawPos.x, m_vDrawPos.y - m_vDrawSize.y, 0.0f };
    m_VertexList[2].t = { m_rtUV.x1,m_rtUV.y1 + m_rtUV.h };

   /* m_VertexList[3].p = m_VertexList[2].p;
    m_VertexList[3].t = m_VertexList[2].t;

    m_VertexList[4].p = m_VertexList[1].p;
    m_VertexList[4].t = m_VertexList[1].t;*/

    m_VertexList[3].p = { m_vDrawPos.x + m_vDrawSize.x, m_vDrawPos.y - m_vDrawSize.y, 0.0f };
    m_VertexList[3].t = { m_rtUV.x1 + m_rtUV.w,m_rtUV.y1 + m_rtUV.h };

    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);
}
void KObject2D::SetRect(KRect rt)
{
    m_rtInit = rt;
    m_pkImageSize.x = m_pTexture->m_Desc.Width;
    m_pkImageSize.y = m_pTexture->m_Desc.Height;
    //image w,h
    //사실상 정점에 들어가는 uv값
    m_rtUV.x1 = rt.x1 / m_pkImageSize.x;//u
    //1
    m_rtUV.y1 = rt.y1 / m_pkImageSize.y;//v
    //40
    m_rtUV.w = rt.w / m_pkImageSize.x;
    //60
    m_rtUV.h = rt.h / m_pkImageSize.y;

}

// 화면 좌표 -> NDC 좌표 
void  KObject2D::ScreenToNDC()
{
    KVector2D	vDrawSize;
    vDrawSize.x = m_rtInit.w / 2.0f;
    vDrawSize.y = m_rtInit.h / 2.0f;
    m_rtCollision.Set(
        m_vPos.x - vDrawSize.x,
        m_vPos.y - vDrawSize.y,
        m_rtInit.w,
        m_rtInit.h);
    // 0  ~ 800   -> 0~1 ->  -1 ~ +1 
    m_vDrawPos.x = (m_rtCollision.x1 / g_rtClient.right) * 2.0f - 1.0f;
    m_vDrawPos.y = -((m_rtCollision.y1 / g_rtClient.bottom) * 2.0f - 1.0f);
    m_vDrawSize.x = (m_rtInit.w / g_rtClient.right) * 2;
    m_vDrawSize.y = (m_rtInit.h / g_rtClient.bottom) * 2;
}

//월드 좌표(화면 좌표계)->뷰 좌표->NDC좌표
void  KObject2D::ScreenToCamera(KVector2D vCameraPos, KVector2D vViewPort)
{
    KVector2D vPos = m_vPos;//센터값

    KVector2D	vDrawSize;
    vDrawSize.x = m_rtInit.w / 2.0f;
    vDrawSize.y = m_rtInit.h / 2.0f;
    m_rtCollision.Set(
        vPos.x - vDrawSize.x,
        vPos.y - vDrawSize.y,
        m_rtInit.w,
        m_rtInit.h);//위치가 어디냐
    //왼쪽 상단이 이거다
    vPos.x = m_rtCollision.x1 - vCameraPos.x;//화면 좌표계로 바꿔라 센터가 화면좌표계로 ㄱ바뀐다
    vPos.y = m_rtCollision.y1 - vCameraPos.y;

    // 0  ~ 800   -> 0~1 ->  -1 ~ +1여기가 스크린 투 카메라 부분
    m_vDrawPos.x = vPos.x * (2.0f / vViewPort.x);
    m_vDrawPos.y = vPos.y * (2.0f / vViewPort.y) * -1.0f;


    m_vDrawSize.x = (m_rtInit.w / vViewPort.x) * 2;
    m_vDrawSize.y = (m_rtInit.h / vViewPort.y) * 2;

}

void KObject2D::SetPosition(KVector2D vPos)
{
    m_vPos = vPos;//앞으로 렉트의 정중앙이다
    ScreenToNDC();//
    UpdateVertexBuffer();
}
//vPos(화면 좌표)를 ndc 좌표로 변경(컨버팅)해야한다
//화면 좌표로 세팅하고 내부적으로 ndc로 랜더링을한다
//ndc좌표를 만들어주는 기능이 필요하다
void KObject2D::SetPosition(KVector2D vPos, KVector2D vCamera)
{
    m_vPos = vPos;
    ScreenToCamera(vCamera, m_vViewSize);
    UpdateVertexBuffer();
}
bool KObject2D::Frame()
{

    return true;
}