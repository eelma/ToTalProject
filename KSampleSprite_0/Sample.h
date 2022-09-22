#pragma once
#include "KGameCore.h"
#include"KBaseObject.h"

class KUser2D :public KBaseObject
{
public:
	KTexture* m_pTexture;
	POINT m_pkImageSize;
	RECT m_rt;//이미지에 대한 크기
	KRect m_rtInit;
	KRect m_rtUV;
	KVector2D m_vPos;
	KVector2D m_vSize;

public:
	void SetPosition(KVector2D vPos);
	void SetRect(KRect rt);
	void UpdateVertexBuffer();



};
class Sample : public KGameCore
{
	KUser2D*				 m_pUser;
	vector<KBaseObject*> m_pObjectList;

public:
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제
};

