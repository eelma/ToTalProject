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
   
    m_rtUV.x1 = rt.x1 / m_pkImageSize.x;
    
    m_rtUV.y1 = rt.y1 / m_pkImageSize.y;
    
    m_rtUV.w = rt.w / m_pkImageSize.x;
    
    m_rtUV.h = rt.h / m_pkImageSize.y;

}

void KObject2D::SetPosition(KVector2D vPos)
{
    m_vPos = vPos;
    ScreenToNDC();
    UpdateVertexBuffer();
}
bool KObject2D::Frame()
{

    return true;
}

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

    m_vDrawPos.x = (m_rtCollision.x1 / g_rtClient.right) * 2.0f - 1.0f;
    m_vDrawPos.y = -((m_rtCollision.y1 / g_rtClient.bottom) * 2.0f - 1.0f);
    m_vDrawSize.x = (m_rtInit.w / g_rtClient.right) * 2;
    m_vDrawSize.y = (m_rtInit.h / g_rtClient.bottom) * 2;
}