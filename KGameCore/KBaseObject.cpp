#include "KBaseObject.h"
namespace TDX
{
    ID3D11Buffer* CreateVertexBuffer(ID3D11Device* pd3dDevice,
        void* pDataAddress,
        UINT iNumVertex,
        UINT iVertexSize)
    {
        HRESULT hr;
        ID3D11Buffer* pVB = nullptr;
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.ByteWidth = iVertexSize * iNumVertex;//바이트 용량
        //GPU 메모리에 할당
        bd.Usage = D3D11_USAGE_DEFAULT;//버퍼의 할당 장소 내지는 버퍼용도
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = pDataAddress;
        hr = pd3dDevice->CreateBuffer(
            &bd,
            &sd,
            &pVB
        );
        return pVB;


    }
}
void		KBaseObject::CreateConstantData()
{
    D3DXMatrixIdentity(&m_cbData.matWorld);
    D3DXMatrixIdentity(&m_cbData.matView);
    D3DXMatrixIdentity(&m_cbData.matProj);
    m_cbData.fTimer = 0.0f;
    D3DXMatrixTranspose(&m_cbData.matWorld, &m_cbData.matWorld);
    D3DXMatrixTranspose(&m_cbData.matView, &m_cbData.matView);
    D3DXMatrixTranspose(&m_cbData.matProj, &m_cbData.matProj);
    
}
HRESULT		KBaseObject::CreateConstantBuffer()
{
    HRESULT hr;
    CreateConstantData();
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(VS_CONSTANT_BUFFER) * 1; // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_cbData;
    hr = m_pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &m_pConstantBuffer);
    return hr;
}
void    KBaseObject::CreateVertexData()
{
    if (m_VertexList.size() > 0)
    {
        m_InitVertexList = m_VertexList;
        return;
    }
    m_VertexList.resize(4);
    m_VertexList[0].p = { -1.0f, 1.0f, 0.0f };
    m_VertexList[1].p = { +1.0f, 1.0f,  0.0f };
    m_VertexList[2].p = { -1.0f, -1.0f, 0.0f };
    m_VertexList[3].p = { 1.0f, -1.0f, 0.0f };

    m_VertexList[0].c = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_VertexList[1].c = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_VertexList[2].c = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_VertexList[3].c = { 1.0f, 1.0f, 1.0f, 1.0f };

    m_VertexList[0].t = { 0.0f, 0.0f };
    m_VertexList[1].t = { 1.0f, 0.0f };
    m_VertexList[2].t = { 0.0f, 1.0f };
    m_VertexList[3].t = { 1.0f, 1.0f };
    m_InitVertexList = m_VertexList;
}
void    KBaseObject::CreateIndexData()
{
    if (m_IndexList.size() > 0)return;
    // 정점버퍼에 인덱스
    m_IndexList.resize(6);
    m_IndexList[0] = 0;
    m_IndexList[1] = 1;
    m_IndexList[2] = 2;
    m_IndexList[3] = 2;
    m_IndexList[4] = 1;
    m_IndexList[5] = 3;

    m_dwFace = m_IndexList.size() / 3;
}
HRESULT KBaseObject::CreateVertexBuffer()
{
    HRESULT hr;
    CreateVertexData();

    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(PNCT_VERTEX) * m_VertexList.size(); // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_VertexList.at(0);
    hr = m_pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &m_pVertexBuffer);
    return hr;
}
HRESULT KBaseObject::CreateIndexBuffer()
{
    HRESULT hr;
    // 정점버퍼에 인덱스
    CreateIndexData();

    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DWORD) * m_IndexList.size(); // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_IndexList.at(0);
    hr = m_pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &m_pIndexBuffer);
    return hr;
}
bool KBaseObject::CreateShader(wstring filename)
{

    m_pShader = I_Shader.Load(filename);
    if (m_pShader)
    {
        m_pVS = m_pShader->m_pVS;
        m_pPS = m_pShader->m_pPS;
        m_pVSCode = m_pShader->m_pVSCode;
        return true;
    }

    /*m_pVS = m_pShader->m_pVS;
    m_pPS = m_pShader->m_pPS;
    m_pVSCode = m_pShader->m_pVSCode;
    return true;*/

    return false;
}
HRESULT KBaseObject::CreateVertexShader(wstring filename)
{
    HRESULT hr;
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
        return false;
    }
    hr = m_pd3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);
    return hr;
}
HRESULT KBaseObject::CreatePixelShader(wstring filename)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;
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
    return hr;
}
HRESULT KBaseObject::CreateVertexLayout()
{
    HRESULT hr;
    if (m_pVSCode == nullptr)
    {
        return E_FAIL;
    }
    // 정점레이아웃은 정점쉐이더 밀접한 관련.
    // 정점레이아웃 생성시 사전에 정점쉐이더 생성이 필요하다.
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,24,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,40,D3D11_INPUT_PER_VERTEX_DATA, 0},
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

bool	KBaseObject::Create(
    ID3D11Device* pd3dDevice,// 디바이스 객체
    ID3D11DeviceContext* pImmediateContext,
    wstring shadername,
    wstring texturename)
{
    m_pd3dDevice = pd3dDevice;
    m_pImmediateContext = pImmediateContext;
    m_szShaderName = shadername;
    m_szTextureName = texturename;
    if (FAILED(CreateConstantBuffer()))
    {
        return false;
    }
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateIndexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateShader(shadername)))
    {
        return false;
    }
    /*if (FAILED(CreateVertexShader(shadername)))
    {
        return false;
    }
    if (FAILED(CreatePixelShader(shadername)))
    {
        return false;
    }*/
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }
    if(LoadTexture(texturename))
    {
        m_pTextureSRV = m_pTexture->m_pTextureSRV;
    }
    if (!Init())
    {
        return false;
    }
    return true;
}
bool KBaseObject::Init()
{
    return true;
}
bool KBaseObject::Frame()
{

    return true;
}
void   KBaseObject::UpdateVertexBuffer()
{
    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, nullptr,
        &m_VertexList.at(0), 0, 0);
}
void   KBaseObject::UpdateConstantBuffer()
{
    m_cbData.matWorld = m_matWorld.Transpose();
    m_cbData.matView = m_matView.Transpose();
    m_cbData.matProj = m_matProj.Transpose();
    m_pImmediateContext->UpdateSubresource(
        m_pConstantBuffer, 0, nullptr,
        &m_cbData, 0, 0);
}

void	KBaseObject::SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj)
{
    if (matWorld != nullptr)
    {
        m_matWorld = *matWorld;
    }
    if (matView != nullptr)
    {
        m_matView = *matView;
    }
    if (matProj != nullptr)
    {
        m_matProj = *matProj;
    }
    UpdateConstantBuffer();
}
bool KBaseObject::Render()
{

    PreRender();
    PostRender();
    return true;
}
bool KBaseObject::PreRender()
{
   

    m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTextureSRV);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);
    UINT stride = sizeof(PNCT_VERTEX); // 정점1개의 바이트용량
    UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
    m_pImmediateContext->IASetVertexBuffers(0, 1,
        &m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer,
        DXGI_FORMAT_R32_UINT, 0);
    m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

    return true;
}

bool KBaseObject::PostRender()
{
 
    if (m_pIndexBuffer == nullptr)
        m_pImmediateContext->Draw(m_VertexList.size(), 0);
    else
        m_pImmediateContext->DrawIndexed(m_dwFace*3, 0, 0);

    return true;
}
bool KBaseObject::Release()
{
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pIndexBuffer) m_pIndexBuffer->Release();
    if (m_pConstantBuffer) m_pConstantBuffer->Release();
    if (m_pVertexLayout) m_pVertexLayout->Release();
    /* if (m_pVS) m_pVS->Release();
     if (m_pPS) m_pPS->Release();
     if (m_pVSCode) m_pVSCode->Release();
     if (m_pPSCode) m_pPSCode->Release();*/
    return true;
}

bool KBaseObject::LoadTexture(W_STR texturename)
{
    m_pTexture = I_Tex.Load(texturename);
    if (m_pTexture != nullptr)
    {
        m_pTextureSRV = m_pTexture->m_pTextureSRV;
        return true;
    }
    return false;
}


