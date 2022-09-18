#include "Sample.h"
HRESULT Sample::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC ��ǥ�� ����
    // x -> -1 ~ +1
    // y -> -1 ~ +1
    // z -> 0 ~  +1
    // +1 V0--------v1
    //           /
    // -1      0,0     +1
    //       /
    // -1 v2
    // float  0  ~ 7
    // pos    0 ~ 3,  0~ 11
    // color  4 ~ 7   12~
    SimpleVertex vertices[] =
    {
        -1.0f, 1.0f,  0.0f, //0.0f,0.0f,0.0f,0.0f,// v0
        +1.0f, 1.0f,  0.0f, //0.0f,0.0f,0.0f,0.0f,// v1
        -1.0f, -1.0f, 0.0f, //0.0f,0.0f,0.0f,0.0f,// v2
    };
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth    = sizeof(SimpleVertex)*3; // ����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage        = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���ۿ뵵
    bd.BindFlags    = D3D11_BIND_VERTEX_BUFFER;
    
    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = vertices;    
    hr=m_pd3dDevice->CreateBuffer(
        &bd, // ���� �Ҵ�
        &sd, // �ʱ� �Ҵ�� ���۸� ü��� CPU�޸� �ּ�
        &m_pVertexBuffer);
    return hr;
}
HRESULT Sample::CreateVertexLayout()
{
    HRESULT hr;  
    // �������̴� ������ 


    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(
        L"VertexShader.txt",
        NULL,
        NULL,
        "main",
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
        return false;
    }
    hr = m_pd3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);

    // �Ƚ����̴� ������  
    hr = D3DCompileFromFile(
        L"PixelShader.txt",
        NULL,
        NULL,
        "PSMain",
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
        return false;
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
        return false;
    }
    // �������̾ƿ��� �������̴� ������ ����.
    // �������̾ƿ� ������ ������ �������̴� ������ �ʿ��ϴ�.
    D3D11_INPUT_ELEMENT_DESC ied []=
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
        //{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    hr = m_pd3dDevice->CreateInputLayout(
        ied,
        NumElements,
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
         &m_pVertexLayout);
    
    return hr;
}
bool	Sample::Init()
{   
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }
    return true;
}
bool		Sample::Frame()
{
    return true;
}
bool		Sample::Render()
{
    // �ﰢ�� ������
    UINT stride = sizeof(SimpleVertex); // ����1���� ����Ʈ�뷮
    UINT offset = 0; // �������ۿ��� �������(����Ʈ)
    //SLOT(�������͸�)
    m_pImmediateContext->IASetVertexBuffers(0, 1,
        &m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);
    m_pImmediateContext->Draw(3, 0);
    return true;
}
bool		Sample::Release()
{
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pVertexLayout) m_pVertexLayout->Release();
    if (m_pVS) m_pVS->Release();
    if (m_pPS) m_pPS->Release();
    if (m_pVSCode) m_pVSCode->Release();
    if (m_pPSCode) m_pPSCode->Release();  
    return true;
}


GAME_RUN(P2_CreateDevice_0, 1024, 768)