#pragma once
#include"KStd.h"
class KTimer:public KSingleTone<KTimer>
{
public:
	//타이머의 핵심 기능
	float m_fGameTimer = 0.0f;
	float m_fElapseTimer = 10.0f;
	UINT m_iFPS = 0;
	wstring m_szTimer;

	//템프
private:
	DWORD m_dwBeforeTime;
	UINT m_iFPSCounter = 0;
	float m_fFPSTimer = 0.0f;

public:
	virtual bool		Init(); // 초기화
	virtual bool		Frame();// 실시간 계산
	virtual bool		Render();// 실시간 랜더링
	virtual bool		Release();// 소멸 및 삭제
};

//I = 인터페이스
#define I_Timer KTimer::GetInstance()