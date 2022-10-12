#include "KUser2D.h"
#include"KInput.h"
bool KUser2D::Frame()
{
    KVector2D vPos = m_vPos;
    if (I_Input.GetKey('W'))
    {
        vPos.y += -1.0f * g_fSecondPerFrame * m_fSpeed;
    }
    if (I_Input.GetKey('S'))
    {
        vPos.y += 1.0f * g_fSecondPerFrame * m_fSpeed;
    }
    if (I_Input.GetKey('A'))
    {
        vPos.x += -1.0f * g_fSecondPerFrame * m_fSpeed;
    }
    if (I_Input.GetKey('D'))
    {
        vPos.x += 1.0f * g_fSecondPerFrame * m_fSpeed;
    }
    if (vPos.x > g_rtClient.right)
    {
        vPos.x = g_rtClient.left;
    }if (vPos.x < g_rtClient.left)
    {
        vPos.x = g_rtClient.right;
    }
    SetPosition(vPos);
    return true;
}
