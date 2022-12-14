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

	D3DXVec3Normalize(&m_vRight,&m_vRight);
	D3DXVec3Normalize(&m_vUp,&m_vUp);
	D3DXVec3Normalize(&m_vLook,&m_vLook);

}
void KCamera::CreateViewMatrix(TVector3 vEye, TVector3 vAt, TVector3 vUp)
{

	m_vPos = vEye;
	m_vTarget = vAt;
	m_vUp = vUp;
	D3DXMatrixLookAtLH(&m_matView, &vEye, &vAt, &vUp);
	//m_matView.ViewLookAt(vEye, vAt, vUp);
	Update();

}

void KCamera::CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio)
{

	m_fNear = fNear;
	m_fFar = fFar;
	m_fFovY = fFovY;
	m_fAspectRatio = fAspectRatio;
	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspectRatio, m_fNear, m_fFar);
	//PerspectiveFovLH(m_matProj, m_fNear, m_fFar, m_fFovY, m_fAspectRatio);

}

bool KCamera::Frame()
{

	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		TVector3 v = m_vLook * 10.0f * g_fSecondPerFrame;
		m_vPos += v;
	}
	if (I_Input.GetKey('S') == KEY_HOLD)
	{
		TVector3 v = m_vLook * -10.0f * g_fSecondPerFrame;
		m_vPos += v;
	}
	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		TVector3 v = m_vRight * 10.0f * g_fSecondPerFrame;
		m_vPos += v;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		TVector3 v = m_vRight * -10.0f * g_fSecondPerFrame;
		m_vPos += v;
	}
	if (I_Input.GetKey('Q') == KEY_HOLD)
	{
		TVector3 v = m_vUp * 10.0f * g_fSecondPerFrame;
		m_vPos += v;
	}
	if (I_Input.GetKey('E') == KEY_HOLD)
	{
		TVector3 v = m_vUp * -10.0f * g_fSecondPerFrame;
		m_vPos += v;
	}

	TVector3 vUp = { 0,1,0 };
	D3DXMatrixLookAtLH(&m_matView, &m_vPos,&m_vTarget, &m_vUp);
	//m_matView.ViewLookAt(m_vPos, m_vTarget, m_vUp);

	Update();
	return true;
}
