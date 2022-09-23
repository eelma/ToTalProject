#pragma once
#include "KGameCore.h"
#include"KBaseObject.h"
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
class KUser2D :public KObject2D
{

public:
	bool Frame()override;
};
class KNpc2D :public KObject2D
{

public:
	bool Frame()override;
	
};
class Sample : public KGameCore
{
	KBaseObject*			m_pMap;
	vector<KBaseObject*>	m_pNpcList;
	KUser2D*				m_pUser;
	vector<KBaseObject*>	m_pObjectList;

public:
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제
};

