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
	KVector2D m_vPos;
	//	KVector2D m_vSize;
	KVector2D m_vDir;
	KVector2D	m_vNDCPos;
	KVector2D	m_vBeforePos;
	KVector2D	m_vOffsetPos;



	float m_fSpeed = 100.0f;
public:
	KVector2D m_vDrawPos;
	KVector2D m_vDrawSize;

public:
	KVector2D m_vCameraPos;
	KVector2D m_vViewSize;
	void SetCameraPos(KVector2D vCamera) { m_vCameraPos = vCamera; }
	void SetCameraSize(KVector2D vSize) { m_vViewSize = vSize; }
	void ScreenToNDC();
	void ScreenToCamera(KVector2D vCameraPos,
		KVector2D vViewPort = {2000.0f,2000.0f});
public:
	bool Frame()override;
	virtual void SetRect(KRect vPos);
	virtual void SetPosition(KVector2D vPos);
	virtual void SetPosition(KVector2D vPos, KVector2D vCamera);
	virtual void SetDirection(KVector2D vDir)
	{
		m_vDir = vDir;
	}
	virtual void UpdateVertexBuffer()override;
	virtual void SetMask(KTexture* pMaskTex)
	{
		m_pMaskTex = pMaskTex;
	}
};
