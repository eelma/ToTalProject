#include "Sample.h"

bool	Sample::Init()
{
   
    return true;
}
bool		Sample::Frame()
{
    if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
    {
        INT K = 0;
    }
    if (I_Input.GetKey(VK_LBUTTON) == KEY_UP)
    {
        INT K = 0;
    }
    if (I_Input.GetKey('W') == KEY_PUSH)
    {
        INT K = 0;
    }
    if (I_Input.GetKey('W') == KEY_UP)
    {
        INT K = 0;
    }
    if (I_Input.GetKey('A') == KEY_PUSH)
    {
        INT K = 0;
    }
    if (I_Input.GetKey('S') == KEY_PUSH)
    {
        INT K = 0;
    }
    if (I_Input.GetKey('D') == KEY_PUSH)
    {
        INT K = 0;
    }
        return true;
}
bool		Sample::Render()
{
   
    return true;
}
bool		Sample::Release()
{
    return true;
}


GAME_RUN(KGameCore, 1024, 768)
