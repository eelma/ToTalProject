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
    //��ǻ� ������ ���� uv��
    m_rtUV.x1 = rt.x1 / m_pkImageSize.x;//u
    //1
    m_rtUV.y1 = rt.y1 / m_pkImageSize.y;//v
    //40
    m_rtUV.w = rt.w / m_pkImageSize.x;
    //60
    m_rtUV.h = rt.h / m_pkImageSize.y;

}

// ȭ�� ��ǥ -> NDC ��ǥ 
void  KObject2D::ScreenToNDC()
{
    // 0  ~ 800   -> 0~1 ->  -1 ~ +1
    m_vDrawPos.x = (m_vPos.x / g_rtClient.right) * 2.0f - 1.0f;
    m_vDrawPos.y = -((m_vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
    m_vDrawSize.x = (m_rtInit.w / g_rtClient.right) * 2;
    m_vDrawSize.y = (m_rtInit.h / g_rtClient.bottom) * 2;
}

void  KObject2D::ScreenToCamera(KVector2D vCameraPos, KVector2D vViewPort)
{
    KVector2D vPos = m_vPos;
    vPos.x = vPos.x - vCameraPos.x;
    vPos.y = vPos.y - vCameraPos.y;
    // 0  ~ 800   -> 0~1 ->  -1 ~ +1
    m_vDrawPos.x = vPos.x * (2.0f / vViewPort.x);
    m_vDrawPos.y = vPos.y * (2.0f / vViewPort.y) * -1.0f;


    m_vDrawSize.x = (m_rtInit.w / vViewPort.x) * 2;
    m_vDrawSize.y = (m_rtInit.h / vViewPort.y) * 2;

}

void KObject2D::SetPosition(KVector2D vPos)
{
    m_vPos = vPos;
    ScreenToNDC();
    UpdateVertexBuffer();
}
//vPos(ȭ�� ��ǥ)�� ndc ��ǥ�� ����(������)�ؾ��Ѵ�
//ȭ�� ��ǥ�� �����ϰ� ���������� ndc�� ���������Ѵ�
//ndc��ǥ�� ������ִ� ����� �ʿ��ϴ�
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