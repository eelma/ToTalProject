#include "KTimer.h"
bool		KTimer::Init()
{
    m_fGameTimer = 0.0f;
    m_fElapseTimer = 10;
    dwBeforeTime = timeGetTime();
    return true;
}
bool		KTimer::Frame()
{
    DWORD dwCurrentTime = timeGetTime();
    DWORD dwElapseTime = dwCurrentTime - dwBeforeTime;
    m_fElapseTimer = dwElapseTime / 1000.0f;
    m_fGameTimer += m_fElapseTimer;

    dwBeforeTime = dwCurrentTime;
    counter++;
    fFps += m_fElapseTimer;
    if (fFps >= 1.0f)
    {
        fps = counter;
        counter = 0;
        fFps = fFps - 1.0f;
    }
    

    return true;
}
bool		KTimer::Render()
{
    wstring timer = to_wstring(m_fGameTimer);
    timer += L" ";
    timer += to_wstring(fps);
    timer += L"\n";

    OutputDebugString(timer.c_str());

    return true;
}
bool		KTimer::Release()
{
    return true;
}
