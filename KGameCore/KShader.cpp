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
    m_pVS = nullptr;
    m_pPS = nullptr;
    m_pVSCode = nullptr;
    m_pPSCode = nullptr;
    return true;
}
HRESULT KShader::Load(ID3D11Device* pd3dDevice,
    ID3D11DeviceContext* pImmediateContext,
    wstring filename)
{
    HRESULT  hr;
    m_pd3dDevice = pd3dDevice;
    m_pImmediateContext = pImmediateContext;

    // 정점쉐이더 컴파일 
    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        "VS",
        "vs_5_0",
        0,
        0,
        &m_pVSCode,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }
    hr = m_pd3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);

    // 픽쉘쉐이더 컴파일  
    hr = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        "PS",
        "ps_5_0",
        0,
        0,
        &m_pPSCode,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }
    hr = m_pd3dDevice->CreatePixelShader(
        m_pPSCode->GetBufferPointer(),
        m_pPSCode->GetBufferSize(),
        NULL,
        &m_pPS);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    return hr;

}