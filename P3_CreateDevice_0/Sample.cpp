#include "Sample.h"



bool Sample::Init()
{
    KDevice::Init();

    return true;
}

bool Sample::Frame()
{
    KDevice::Frame();
    return true;
}

bool Sample::Render()
{

    KDevice::Render();
   
    return true;
}

bool Sample::Release()
{
    KDevice::Release();
    return true;
}


GAME_RUN(P2_CreateDeice_0,1024,768);
