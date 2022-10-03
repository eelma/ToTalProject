#pragma once
#include"KGameCore.h"
#include"KBaseObject.h"
#include"KUser2D.h"
#include"KMapObject.h"

typedef vector<RECT> RECT_ARRAY;//렉트 배열

class KSprite : public KObject2D
{

	
public:
	void SetPosition(KVector2D vPos)
	{
		m_vPos = vPos;//얘가 센터값
		KVector2D	vDrawSize;
		vDrawSize.x = m_rtInit.w / 2.0f;
		vDrawSize.y = m_rtInit.h / 2.0f;
		m_rtCollision.Set(
			vPos.x - vDrawSize.x,
			vPos.y - vDrawSize.y,
			m_rtInit.w,
			m_rtInit.h);
		// 0  ~ 800   -> 0~1 ->  -1 ~ +1
		m_vDrawPos.x = (m_rtCollision.x1 / g_rtClient.right) * 2.0f - 1.0f;
		m_vDrawPos.y = -((m_rtCollision.y1 / g_rtClient.bottom) * 2.0f - 1.0f);
		m_vDrawSize.x = (m_rtInit.w / g_rtClient.right) * 2;
		m_vDrawSize.y = (m_rtInit.h / g_rtClient.bottom) * 2;
		UpdateVertexBuffer();
	}

};
class Sample : public KGameCore
{
	KMapObject* m_pMap;
	KVector2D m_vCamera;
	KUser2D* m_pUser;
	KSprite* m_pObject;
	vector<RECT_ARRAY>m_rtSpriteList;//2차원 배열

public:
	bool GameDataLoad(const TCHAR* pszLoad);
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
	//virtual bool Run()override;

};

