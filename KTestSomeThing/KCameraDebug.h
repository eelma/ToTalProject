#pragma once
#include "KCamera.h"
#include"KFrustum.h"
class KCameraDebug : public KCamera
{
public:
	KFrustum m_vFrustum;
public:
	virtual void CreateViewMatrix(KVector vEye, KVector vAt, KVector vUp);
	virtual void CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool Frame();
	virtual void Update()override;
};

