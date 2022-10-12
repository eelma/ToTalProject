#include "KInput.h"

bool KInput::Init()
{
    ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
    return true;
}
DWORD KInput::GetKey(DWORD dwkey)
{
    return m_dwKeyState[dwkey];
}
bool KInput::Frame()
{
    ::GetCursorPos(&m_ptPos);
    ::ScreenToClient(g_hWnd, &m_ptPos);

    for (int iKey = 0; iKey < 256; iKey++)
    {
        SHORT sKey = ::GetAsyncKeyState(iKey);
        if (sKey & 0x8000)
        {
            if (m_dwKeyState[iKey] == KEY_FREE || m_dwKeyState[iKey] == KEY_UP)
                m_dwKeyState[iKey] = KEY_PUSH;
            else
                m_dwKeyState[iKey] = KEY_HOLD;
        }
        else
        {
            if (m_dwKeyState[iKey] == KEY_PUSH || m_dwKeyState[iKey] == KEY_HOLD)
                m_dwKeyState[iKey] = KEY_UP;
            else
                m_dwKeyState[iKey] = KEY_FREE;
        }
    }
    return true;
}

bool KInput::Render()
{
    return true;
}

bool KInput::Release()
{
    return true;
}
