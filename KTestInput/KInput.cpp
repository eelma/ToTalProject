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
    ::GetCursorPos(&m_ptPos);//ȭ����ǥ ȭ����ü�� ���� ��ǥ
    ::ScreenToClient(g_hWnd, &m_ptPos);//Ŭ���̾�Ʈ�� ���� ��ǥ

    for (int iKey = 0; iKey < 256; iKey++)
    {
        SHORT sKey = ::GetAsyncKeyState(iKey);//�񵿱�(���� �ٸ� �ð���) Ű ����
        if (sKey & 0x8000)//�ֻ��� ��Ʈ���� �������� �������Ŀ����� ���� ��ȯ���� Ȯ�εȴ�
                          //�ֻ��� ��Ʈ�� 1�̸� ��������
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
