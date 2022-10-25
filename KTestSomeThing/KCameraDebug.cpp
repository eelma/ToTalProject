#include "KCameraDebug.h"
#include"KInput.h"
#include"TMath.h"
void KCameraDebug::CreateViewMatrix(KVector vEye, KVector vAt, KVector vUp)
{
    m_vPos = vEye;
    m_vTarget = vAt;
    m_vUp = vUp;
    m_matView.ViewLookAt(vEye, vAt, vUp);
}

void KCameraDebug::CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio)
{
    m_fNear = fNear;
    m_fFar = fFar;
    m_fFovY = fFovY;
    m_fAspectRatio = fAspectRatio;
    PerspectiveFovLH(m_matProj, m_fNear, m_fFar, m_fFovY, m_fAspectRatio);
    //m_matProj.OrthoLH(800, 600, 0.0f, 100.0f);
    //OrthoOffCenterLH(m_matProj, -400, 400, -300, 300, 0.0f, 100.f);

}

bool KCameraDebug::Frame()
{
    if (I_Input.GetKey('W') == KEY_HOLD)
    {
        KVector v = m_vLook * 10.0f * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('S') == KEY_HOLD)
    {
        KVector v = m_vLook * -10.0f * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('A') == KEY_HOLD)
    {
        KVector v = m_vRight * 10.0f * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('D') == KEY_HOLD)
    {
        KVector v = m_vRight * -10.0f * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('Q') == KEY_HOLD)
    {
        KVector v = m_vUp * 10.0f * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('E') == KEY_HOLD)
    {
        KVector v = m_vUp * -10.0f * g_fSecondPerFrame;
        m_vPos += v;
    }
    Update();

    return true;
}
