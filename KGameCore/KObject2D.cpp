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
    float fPixelX = (1.0f / m_pTexture->m_Desc.Width) / 2.0f;
    float fPixelY = (1.0f / m_pTexture->m_Desc.Height) / 2.0f;
    // 90  -> 0 ~ 1
    m_rtUV.x1 = rt.x1 / m_pkImageSize.x + fPixelX; // u
    // 1
    m_rtUV.y1 = rt.y1 / m_pkImageSize.y + fPixelY; // v
    // 40
    m_rtUV.w = rt.w / m_pkImageSize.x;
    // 60
    m_rtUV.h = rt.h / m_pkImageSize.y;

}

// ȭ?? ??ǥ -> NDC ??ǥ 
void  KObject2D::ScreenToNDC()
{
    TVector2	vDrawSize;
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

//???? ??ǥ(ȭ?? ??ǥ??)->?? ??ǥ->NDC??ǥ
void  KObject2D::ScreenToCamera(TVector2 vCameraPos, TVector2 vViewPort)
{
    TVector2 vPos = m_vPos;//???Ͱ?

    TVector2	vDrawSize;
    vDrawSize.x = m_rtInit.w / 2.0f;
    vDrawSize.y = m_rtInit.h / 2.0f;
    m_rtCollision.Set(
        vPos.x - vDrawSize.x,
        vPos.y - vDrawSize.y,
        m_rtInit.w,
        m_rtInit.h);//??ġ?? ??????
    //???? ?????? ?̰Ŵ?
    vPos.x = m_rtCollision.x1 - vCameraPos.x;//ȭ?? ??ǥ???? ?ٲ??? ???Ͱ? ȭ????ǥ???? ???ٲ???
    vPos.y = m_rtCollision.y1 - vCameraPos.y;

    // 0  ~ 800   -> 0~1 ->  -1 ~ +1???Ⱑ ??ũ?? ?? ī?޶? ?κ?
    m_vDrawPos.x = vPos.x * (2.0f / vViewPort.x);
    m_vDrawPos.y = vPos.y * (2.0f / vViewPort.y) * -1.0f;


    m_vDrawSize.x = (m_rtInit.w / vViewPort.x) * 2;
    m_vDrawSize.y = (m_rtInit.h / vViewPort.y) * 2;

}

void KObject2D::SetPosition(TVector2 vPos)
{
    m_vBeforePos = m_vPos;
    m_vPos = vPos;//?????? ??Ʈ?? ???߾??̴?
    ScreenToNDC();//
    UpdateVertexBuffer();
    m_vOffsetPos = m_vPos - m_vBeforePos;

}
//vPos(ȭ?? ??ǥ)?? ndc ??ǥ?? ????(??????)?ؾ??Ѵ?
//ȭ?? ??ǥ?? ?????ϰ? ?????????? ndc?? ?????????Ѵ?
//ndc??ǥ?? ???????ִ? ?????? ?ʿ??ϴ?
void KObject2D::SetPosition(TVector2 vPos, TVector2 vCamera)
{
    m_vPos = vPos;
    ScreenToCamera(vCamera, m_vViewSize);
    UpdateVertexBuffer();
}
bool KObject2D::Frame()
{

    return true;
}