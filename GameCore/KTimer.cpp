#include "KTimer.h"

float g_fGameTimer = 0.0f;
float g_fSecondPerFrame = 10.0f;

bool		KTimer::Init()
{
    m_fGameTimer = 0.0f;
    m_fElapseTimer = 10.f;
    m_dwBeforeTime = timeGetTime();
    return true;
}

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
