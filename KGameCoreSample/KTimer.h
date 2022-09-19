#pragma once
#include"KStd.h"
class KTimer
{
public:
	float m_fGameTimer = 0.0f;
	float m_fElapseTimer = 10;
	UINT m_iFPS = 0;
public:
	DWORD dwBeforeTime;
	UINT fps = 0;
	UINT counter = 0;
	float fFps = 0.0f;

public:
	virtual bool		Init(); // 초기화
	virtual bool		Frame();// 실시간 계산
	virtual bool		Render();// 실시간 랜더링
	virtual bool		Release();// 소멸 및 삭제
};

