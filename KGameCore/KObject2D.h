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
	TVector2 m_vPos;
	//	TVector2 m_vSize;
	TVector2 m_vDir;
	TVector2	m_vNDCPos;
	TVector2	m_vBeforePos;
	TVector2	m_vOffsetPos;



	float m_fSpeed = 100.0f;
public:
	TVector2 m_vDrawPos;
	TVector2 m_vDrawSize;

public:
	TVector2 m_vCameraPos;
	TVector2 m_vViewSize;
	void SetCameraPos(TVector2 vCamera) { m_vCameraPos = vCamera; }
	void SetCameraSize(TVector2 vSize) { m_vViewSize = vSize; }
	void ScreenToNDC();
	void ScreenToCamera(TVector2 vCameraPos,
		TVector2 vViewPort = {2000.0f,2000.0f});
public:
	bool Frame()override;
	virtual void SetRect(KRect vPos);
	virtual void SetPosition(TVector2 vPos);
	virtual void SetPosition(TVector2 vPos, TVector2 vCamera);
	virtual void SetDirection(TVector2 vDir)
	{
		m_vDir = vDir;
	}
	virtual void UpdateVertexBuffer()override;
	virtual void SetMask(KTexture* pMaskTex)
	{
		m_pMaskTex = pMaskTex;
	}
};
