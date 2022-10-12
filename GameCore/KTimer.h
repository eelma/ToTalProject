#pragma once
#include"KStd.h"
#pragma comment(lib,"winmm.lib")
class KTimer:public KSingleTone<KTimer>
{
public:

	float m_fGameTimer = 0.0f;
	float m_fElapseTimer = 10.0f;
	UINT m_iFPS = 0;
	wstring m_szTimer;

private:
	DWORD m_dwBeforeTime;
	UINT m_iFPSCounter = 0;
	float m_fFPSTimer = 0.0f;

public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
};


#define I_Timer KTimer::GetInstance()