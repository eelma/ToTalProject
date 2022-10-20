#pragma once
#include "KBaseObject.h"
class KCamera :public KBaseObject
{

public:
	KVector			m_vCameraPos;
	KVector			m_vTarget = { 0,0,0 };
	KVector			m_vUp = { 0,1,0 };
	float			m_fNear;
	float			m_fFar;
	float			m_fFovY;
	float			m_fAspectRatio;
public:
	virtual void  CreateViewMatrix(KVector vEye, KVector vAt, KVector vUp);
	virtual void  CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool  Frame();

};

