#pragma once
#include"KBaseObject.h"
#include"KCollision.h"
class KObject2D :public  KBaseObject
{
public:
	KTexture* m_pMaskTex = nullptr;
	POINT m_pkImageSize;

	//RECT m_rt;//이미지에 대한 크기

	KRect m_rtInit;
	KRect m_rtUV;
	//스크린의 포지션
	KVector2 m_vPos;
	//	KVector2 m_vSize;
	KVector2 m_vDir;
	KVector2	m_vNDCPos;
	KVector2	m_vBeforePos;
	KVector2	m_vOffsetPos;



	float m_fSpeed = 100.0f;
public:
	KVector2 m_vDrawPos;
	KVector2 m_vDrawSize;

public:
	KVector2 m_vCameraPos;
	KVector2 m_vViewSize;
	void SetCameraPos(KVector2 vCamera) { m_vCameraPos = vCamera; }
	void SetCameraSize(KVector2 vSize) { m_vViewSize = vSize; }
	void ScreenToNDC();
	void ScreenToCamera(KVector2 vCameraPos,
		KVector2 vViewPort = {2000.0f,2000.0f});
public:
	bool Frame()override;
	virtual void SetRect(KRect vPos);
	virtual void SetPosition(KVector2 vPos);
	virtual void SetPosition(KVector2 vPos, KVector2 vCamera);
	virtual void SetDirection(KVector2 vDir)
	{
		m_vDir = vDir;
	}
	virtual void UpdateVertexBuffer()override;
	virtual void SetMask(KTexture* pMaskTex)
	{
		m_pMaskTex = pMaskTex;
	}
};
