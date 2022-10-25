#include "KCamera.h"
#include "KInput.h"
void KCamera::Update()
{

	m_vRight.x = m_matView._11;
	m_vRight.y = m_matView._21;
	m_vRight.z = m_matView._31;

	m_vUp.x = m_matView._12;
	m_vUp.y = m_matView._22;
	m_vUp.z = m_matView._32;

	m_vLook.x = m_matView._13;
	m_vLook.y = m_matView._23;
	m_vLook.z = m_matView._33;
	m_vRight.Normalized();
	m_vUp.Normalized();
	m_vLook.Normalized();
}
void KCamera::CreateViewMatrix(KVector vEye, KVector vAt, KVector vUp)
{

	m_vPos = vEye;
	m_vTarget = vAt;
	m_vUp = vUp;
	m_matView.ViewLookAt(vEye, vAt, vUp);
	Update();

}

void KCamera::CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio)
{

	m_fNear = fNear;
	m_fFar = fFar;
	m_fFovY = fFovY;
	m_fAspectRatio = fAspectRatio;
	PerspectiveFovLH(m_matProj, m_fNear, m_fFar, m_fFovY, m_fAspectRatio);

}

bool KCamera::Frame()
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

	KVector vUp = { 0,1,0 };
	m_matView.ViewLookAt(m_vPos, m_vTarget, m_vUp);

	Update();
    return true;
}
