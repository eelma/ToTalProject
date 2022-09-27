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
    ::GetCursorPos(&m_ptPos);//화면좌표 화면전체에 대한 좌표
    ::ScreenToClient(g_hWnd, &m_ptPos);//클라이언트에 대한 좌표

    for (int iKey = 0; iKey < 256; iKey++)
    {
        SHORT sKey = ::GetAsyncKeyState(iKey);//비동기(서로 다른 시간대) 키 상태
        if (sKey & 0x8000)//최상위 비트값이 눌러졌냐 떼졌느냐에따라서 숏의 반환값이 확인된다
                          //최상위 비트가 1이면 눌러졌다
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
