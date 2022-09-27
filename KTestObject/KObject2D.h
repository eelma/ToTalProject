#pragma once
#include"KBaseObject.h"
#include"KCollision.h"
class KObject2D :public  KBaseObject
{
public:
	KTexture* m_pMaskTex = nullptr;
	POINT m_pkImageSize;
	RECT m_rt;//이미지에 대한 크기
	KRect m_rtInit;
	KRect m_rtUV;
	//스크린의 포지션
	KVector2D m_vPos;
	//	KVector2D m_vSize;
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

};
