#pragma once
#include "KCamera.h"
class KCameraDebug : public KCamera
{
public:
	virtual void CreateViewMatrix(KVector vEye, KVector vAt, KVector vUp);
	virtual void CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool Frame();

};

