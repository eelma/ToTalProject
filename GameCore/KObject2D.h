#pragma once
#include"KBaseObject.h"
#include"KCollision.h"
class KObject2D :public  KBaseObject
{
public:
	KTexture* m_pMaskTex = nullptr;
	POINT m_pkImageSize;
	RECT m_rt;
	KRect m_rtInit;
	KRect m_rtUV;
	KVector2D m_vPos;
	KVector2D m_vDir;
	float m_fSpeed = 100.0f;
private:
	KVector2D m_vDrawPos;
	KVector2D m_vDrawSize;

public:
	bool Frame()override;
	void SetPosition(KVector2D vPos);
	void SetDirection(KVector2D vDir)
	{
		m_vDir = vDir;
	}
	void SetRect(KRect rt);
	void UpdateVertexBuffer();
	void SetMask(KTexture* pMaskTex)
	{
		m_pMaskTex = pMaskTex;
	}
public:
	KVector2D m_vCameraPos;
	KVector2D m_vViewSize;
	void SetCameraPos(KVector2D vCamera) { m_vCameraPos = vCamera; }
	void SetCameraSize(KVector2D vSize) { m_vViewSize = vSize; }
	void ScreenToNDC();
	void ScreenToCamera(KVector2D vCameraPos,
		KVector2D vViewPort = { 2000.0f,2000.0f });

};
