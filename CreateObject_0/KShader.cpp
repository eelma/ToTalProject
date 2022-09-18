#include "KShader.h"
#include "KShaderManager.h"

bool KShader::Init()
{
    return true;
}
bool KShader::Frame()
{
    return true;
}
bool KShader::Render()
{
    return true;
}
bool KShader::Release()
{
    if (m_pVS) m_pVS->Release();
    if (m_pPS) m_pPS->Release();
    if (m_pVSCode) m_pVSCode->Release();
    if (m_pPSCode) m_pPSCode->Release();
    return true;
}
HRESULT KShader::Load(ID3D11Device* pd3dDevice,
    ID3D11DeviceContext* pImmediateContext,
    wstring filename)
{
    HRESULT  hr;
    m_pd3dDevice = pd3dDevice;
    m_pImmediateContext = pImmediateContext;
    I_Shader.Load(filename);
    return hr;
}