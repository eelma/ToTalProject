#include "Sample.h"

bool	Sample::Init()
{
    m_object.m_pd3dDevice = m_pd3dDevice;
    m_object.m_pImmediateContext = m_pImmediateContext;
    m_object.Init();
    return true;
}
bool		Sample::Frame()
{
    m_object.Frame();
    return true;
}
bool		Sample::Render()
{
    m_object.Render();
    return true;
}
bool		Sample::Release()
{
    m_object.Release();
    return true;
}

GAME_RUN(TestBase, 800,600)