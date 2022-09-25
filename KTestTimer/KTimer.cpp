#include "KTimer.h"

float g_fGameTimer = 0.0f;
float g_fSecondPerFrame = 10.0f;

bool		KTimer::Init()
{
    m_fGameTimer = 0.0f;
    m_fElapseTimer = 10.f;
    m_dwBeforeTime = timeGetTime();//1000:1초
    return true;
}

//심각도	코드	설명	프로젝트	파일	줄	비표시 오류(Suppression) 상태
//오류	LNK2019	__imp_timeGetTime"public: virtual bool __cdecl KTimer::Frame(void)" (? Frame@KTimer@@UEAA_NXZ) 함수에서 참조되는 확인할 수 없는 외부 기호	KTestTimer	E : \Project\KTestTimer\KTimer.obj	1
//cpp나 라이브러리 없을때 뜬다
//있는데도 문제가 생기면 코드에 문제가 있다
bool		KTimer::Frame()
{
    DWORD dwCurrentTime = timeGetTime();
    DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime;
    m_fElapseTimer = dwElapseTime / 1000.0f;
    m_fGameTimer += m_fElapseTimer;
    {
    m_iFPSCounter++;
    m_fFPSTimer += m_fElapseTimer;
    if (m_fFPSTimer >= 1.0f)
     {
        m_iFPS = m_iFPSCounter;
        m_iFPSCounter = 0;
        m_fFPSTimer = m_fFPSTimer - 1.0f;
     }
    }
    g_fGameTimer = m_fGameTimer;
    g_fSecondPerFrame = m_fElapseTimer;
    m_dwBeforeTime = dwCurrentTime;


    return true;
}
bool		KTimer::Render()
{
    m_szTimer = to_wstring(m_fGameTimer);
    m_szTimer += L" ";
    m_szTimer += to_wstring(m_iFPS);
    m_szTimer += L"\n";

    OutputDebugString(m_szTimer.c_str());

    return true;
}
bool		KTimer::Release()
{
    return true;
}
