#pragma once
#include "KBaseObject.h"
class KCamera :public KBaseObject
{

public:
	KVector m_vPos;
	KVector m_vLook;
	KVector	m_vUp = { 0,1,0 };
	KVector m_vRight;
	float m_fYaw = 0.0f;
	float m_fPitch = 0.0f;
	float m_fRoll = 0.0f;
	float m_fDistance = 0.0f;
	float m_fSpeed = 10.0f;
	KVector			m_vCameraPos;
	KVector			m_vTarget = { 0,0,0 };
	float			m_fNear;
	float			m_fFar;
	float			m_fFovY;
	float			m_fAspectRatio;
public:
	virtual void  CreateViewMatrix(KVector vEye, KVector vAt, KVector vUp);
	virtual void  CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool  Frame();
	virtual void Update();

};

