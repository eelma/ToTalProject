#pragma once
#include "KGameCore.h"
#include"KBaseObject.h"
class Sample : public KGameCore
{
	vector<KBaseObject*> m_pObjectList;

public:
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제
};

