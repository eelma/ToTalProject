#include "Sample.h"

bool	Sample::Init()
{
   
    return true;
}
bool		Sample::Frame()
{
    /*if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
    {
        INT K = 0;
    }
    if (I_Input.GetKey(VK_LBUTTON) == KEY_UP)
    {
        INT K = 0;
    }
    if (I_Input.GetKey('W') == KEY_PUSH)
    {
        m_Writer.Draw(100, 100, L"WKEY_PUSH");
    }
    if (I_Input.GetKey('W') == KEY_UP)
    {
        m_Writer.Draw(100, 100, L"WKEY_UP");
    }
    if (I_Input.GetKey('A') == KEY_PUSH)
    {
        m_Writer.Draw(100, 100, L"AKEY_PUSH");
    }
    if (I_Input.GetKey('S') == KEY_PUSH)
    {
        m_Writer.Draw(100, 100, L"SKEY_PUSH");
    }
    if (I_Input.GetKey('D') == KEY_PUSH)
    {
        m_Writer.Draw(100, 100, L"WKEY_PUSH");
    }*/
        return true;
}
bool		Sample::Render()
{
    if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
    {
        INT K = 0;
    }
    if (I_Input.GetKey(VK_LBUTTON) == KEY_UP)
    {
        INT K = 0;
    }
    if (I_Input.GetKey('W') == KEY_HOLD)
    {
        m_Writer.Draw(100, 100, L"WKEY_HOLD");
    }
    if (I_Input.GetKey('A') == KEY_HOLD)
    {
        m_Writer.Draw(100, 150, L"AKEY_HOLD");
    }
    if (I_Input.GetKey('S') == KEY_HOLD)
    {
        m_Writer.Draw(100, 200, L"SKEY_HOLD");
    }
    if (I_Input.GetKey('D') == KEY_HOLD)
    {
        m_Writer.Draw(100, 250, L"WKEY_HOLD");
    }
    return true;
}
bool		Sample::Release()
{
    return true;
}


GAME_RUN(KGameCore, 1024, 768)
