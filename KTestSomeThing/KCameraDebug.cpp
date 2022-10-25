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
    if (I_Input.GetKey(VK_SHIFT) == KEY_HOLD)
    {
        m_fSpeed += g_fSecondPerFrame * 100.0f;
    }
    else
    {
        m_fSpeed -= g_fSecondPerFrame * 100.0f;
    }
    m_fSpeed = max(10.0f, m_fSpeed);
    m_fSpeed = min(100.0f, m_fSpeed);
    if (I_Input.GetKey('W') == KEY_HOLD)
    {
        KVector v = m_vLook * m_fSpeed * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('S') == KEY_HOLD)
    {
        KVector v = m_vLook * -m_fSpeed * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('A') == KEY_HOLD)
    {
        KVector v = m_vRight * -m_fSpeed * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('D') == KEY_HOLD)
    {
        KVector v = m_vRight * m_fSpeed * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('Q') == KEY_HOLD)
    {
        KVector v = m_vUp * m_fSpeed * g_fSecondPerFrame;
        m_vPos += v;
    }
    if (I_Input.GetKey('E') == KEY_HOLD)
    {
        KVector v = m_vUp * -m_fSpeed * g_fSecondPerFrame;
        m_vPos += v;
    }

    TBASIS_EX::TVector3 vPos;
    vPos.x = m_vPos.x;
    vPos.y = m_vPos.y;
    vPos.z = m_vPos.z;

    //////////////////////////// DebugCamera ////////////////////////////
    TBASIS_EX::TMatrix matWorld;
    TBASIS_EX::TMatrix matView;
    TBASIS_EX::TMatrix matRotation;
    TBASIS_EX::TQuaternion m_qRotation;
    TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&m_qRotation, m_fYaw, m_fPitch, m_fRoll);
    TBASIS_EX::D3DXMatrixAffineTransformation(&matWorld, 1.0f, NULL, &m_qRotation, &vPos);
    TBASIS_EX::D3DXMatrixInverse(&matView, NULL, &matWorld);
    m_matView = *((KMatrix*)&matView);
    Update();

    return true;
}
