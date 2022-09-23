#include "KNpc2D.h"
bool KNpc2D::Frame()
{
    KVector2D vPos = m_vPos;
    //벡터의 직선의 방정식 &  시간의 동기화
    KVector2D  m_vVelocity = m_vDir * m_fSpeed * g_fSecondPerFrame;
    vPos = vPos + m_vVelocity;
    /* m_fSpeed -= 1.0f*g_fSecondPerFrame;
     if (0 >= m_fSpeed)
     {
         m_fSpeed = rand() % 10;
     }*/

    if (vPos.x > g_rtClient.right)
    {
        vPos.x = g_rtClient.right;
        m_vDir.x *= -1.0f;
    }
    if (vPos.x < 0.0f)
    {
        vPos.x = 0.0f;
        m_vDir.x *= -1.0f;
    }
    if (vPos.y > g_rtClient.bottom)
    {
        vPos.y = g_rtClient.bottom;
        m_vDir.y *= -1.0f;
    }
    if (vPos.y < 0.0f)
    {
        vPos.y = 0.0f;
        m_vDir.y *= -1.0f;
    }

    SetPosition(vPos);
    return true;
}
