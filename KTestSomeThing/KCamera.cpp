#include "KCamera.h"
#include "KInput.h"
void KCamera::CreateViewMatrix(KVector vEye, KVector vAt, KVector vUp)
{

	m_vCameraPos = vEye;
	m_vTarget = vAt;
	m_vUp = vUp;
	m_matView.ViewLookAt(vEye, vAt, vUp);

}

void KCamera::CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio)
{

	m_fNear = fNear;
	m_fFar = fFar;
	m_fFovY = fFovY;
	m_fAspectRatio = fAspectRatio;
	PerspectiveFovLH(m_matProj, 1.0f, 100.0f, 3.141592f * 0.5f, 800.0f / 600.0f);

}

bool KCamera::Frame()
{

	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		m_vCameraPos.z += 10.0f * g_fSecondPerFrame;
		//vTarget.z += 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('S') == KEY_HOLD)
	{
		m_vCameraPos.z -= 10.0f * g_fSecondPerFrame;
		//vTarget.z -= 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		m_vCameraPos.x -= 10.0f * g_fSecondPerFrame;
		//vTarget.x -= 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		m_vCameraPos.x += 10.0f * g_fSecondPerFrame;
		//vTarget.x += 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('Q') == KEY_HOLD)
	{
		m_vCameraPos.y += 10.0f * g_fSecondPerFrame;
		//vTarget.y += 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('E') == KEY_HOLD)
	{
		m_vCameraPos.y -= 10.0f * g_fSecondPerFrame;
		//vTarget.y -= 10.0f * g_fSecondPerFrame;
	}

	KVector vUp = { 0,1,0 };
	m_matView.ViewLookAt(m_vCameraPos, m_vTarget, m_vUp);

    return true;
}
