#pragma once
#include "KBaseObject.h"
#include"KFrustum.h"
class KCamera :public KBaseObject
{
public:
	KFrustum m_vFrustum;
public:
	TVector3 m_vPos;
	TVector3 m_vLook;
	TVector3	m_vUp = { 0,1,0 };
	TVector3 m_vRight;
	float m_fYaw = 0.0f;
	float m_fPitch = 0.0f;
	float m_fRoll = 0.0f;
	float m_fDistance = 0.0f;
	float m_fSpeed = 10.0f;
	TVector3			m_vCameraPos;
	TVector3			m_vTarget = { 0,0,0 };
	float			m_fNear;
	float			m_fFar;
	float			m_fFovY;
	float			m_fAspectRatio;
public:
	virtual void  CreateViewMatrix(TVector3 vEye, TVector3 vAt, TVector3 vUp);
	virtual void  CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool  Frame();
	virtual void Update();

};

