#include "Sample.h"

bool	Sample::Init()
{
    m_object.SetDevice(m_pd3dDevice,m_pImmediateContext);
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

