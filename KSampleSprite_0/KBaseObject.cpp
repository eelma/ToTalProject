#include "KBaseObject.h"
#include"KTextureManager.h"
#include"KShaderManager.h"
void KBaseObject::SetDevice(
    ID3D11Device* pd3dDevice,
    ID3D11DeviceContext* pContext)
{
    m_pd3dDevice = pd3dDevice;
    m_pImmediateContext = pContext;
}
HRESULT KBaseObject::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC 좌표계 공간
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
   


    m_VertexList.resize(6);
    m_VertexList[0].p = {-1.0f, 1.0f,  0.0f};
    m_VertexList[0].c = { 1.0f,1.0f,1.0f,1.0f };
    m_VertexList[0].t = { 0.0f,0.0f };
    m_VertexList[1].p = { +1.0f, 1.0f,  0.0f };
    m_VertexList[1].c = { 1.0f,1.0f,1.0f,1.0f };
    m_VertexList[1].t = { 1.0f,0.0f };
    m_VertexList[2].p = { -1.0f, -1.0f, 0.0f };
    m_VertexList[2].c = { 1.0f,1.0f,1.0f,1.0f };
    m_VertexList[2].t = { 0.0f,1.0f };
    m_VertexList[3].p = { -1.0f, -1.0f, 0.0f };
    m_VertexList[3].c = { 1.0f,1.0f,1.0f,1.0f };
    m_VertexList[3].t = { 0.0f,1.0f };
    m_VertexList[4].p = { +1.0f, 1.0f,  0.0f };
    m_VertexList[4].c = { 1.0f,1.0f,1.0f,1.0f };
    m_VertexList[4].t = { 1.0f,0.0f };
    m_VertexList[5].p = { +1.0f, -1.0f, 0.0f };
    m_VertexList[5].c = { 1.0f,1.0f,1.0f,1.0f };
    m_VertexList[5].t = { 1.0f,1.0f };

    /*m_VertexList[0].t = { 0.0f,0.0f };
    m_VertexList[1].t = { 3.0f,0.0f };
    m_VertexList[2].t = { 0.0f,3.0f };
    m_VertexList[3].t = { 0.0f,3.0f };
    m_VertexList[4].t = { 3.0f,0.0f };
    m_VertexList[5].t = { 3.0f,3.0f };*/
     
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    UINT NumVertex = m_VertexList.size();
    bd.ByteWidth = sizeof(SimpleVertex) * NumVertex; // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도 다이나믹은 cpu도 쓸수는 있다 디폴트로 쓰면 gpu도 읽을수만 있지 쓸수는 없다
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
bool KBaseObject::CreateShader(wstring filename)
{
    HRESULT hr;

    m_pShader= I_Shader.Load(filename);
    if(m_pShader)return true;
    
    return false;
}
HRESULT KBaseObject::CreateVertexLayout()
{
    HRESULT hr;
    // 정점쉐이더 컴파일 

    // 정점레이아웃은 정점쉐이더 밀접한 관련.
    // 정점레이아웃 생성시 사전에 정점쉐이더 생성이 필요하다.
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,28,D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    hr = m_pd3dDevice->CreateInputLayout(
        ied,
        NumElements,
        m_pShader->m_pVSCode->GetBufferPointer(),
        m_pShader->m_pVSCode->GetBufferSize(),
        &m_pVertexLayout);

    return hr;
}
bool KBaseObject::LoadTexture(wstring filename)
{
    HRESULT  hr;
    m_pTexture=I_Tex.Load(filename);
    if (m_pTexture != nullptr)
    {
        
        return true;
    }
    return false;
    
}
bool	KBaseObject::Create(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pContext,
								const wchar_t* texName, const wchar_t* shaderName)
{
    SetDevice(pd3dDevice, pContext);
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateShader(shaderName)))
    {
        return false;
    }
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }
    if (FAILED(LoadTexture(texName)))
    {
        return false;
    }
    return true;
}

bool	KBaseObject::Init()
{
   
    return true;
}
bool		KBaseObject::Frame()
{
    m_VertexList[0].p = { -1.0f, 1.0f,  0.0f };
    m_VertexList[0].c = { 1.0f,0.0f,0.0f,0.0f };
    //gpu update cpu에서 명령하지만 gpu에서 업데이트하게 해준다
    //위치이동

    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
    
    return true;
}
bool		KBaseObject::Render()
{
    PreRender();
    PostRender();
    return true;
}

bool		KBaseObject::PreRender()
{
    // 삼각형 랜더링
    UINT stride = sizeof(SimpleVertex); // 정점1개의 바이트용량
    UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
    //SLOT(레지스터리)
    m_pImmediateContext->IASetVertexBuffers(0, 1,
        &m_pVertexBuffer, &stride, &offset);

    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pShader->m_pVS, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pShader->m_pPS, NULL, 0);

    m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //tex
    //맨 앞 숫자는 pixelshader.txt의 레지스터 번호와 동일해야한다
    ID3D11ShaderResourceView* srv = m_pTexture->GetSRV();
    m_pImmediateContext->PSSetShaderResources(0,1,&srv);
    m_pImmediateContext->Draw(m_VertexList.size(), 0);
    return true;
}
bool		KBaseObject::PostRender()
{
    // 삼각형 랜더링
    UINT stride = sizeof(SimpleVertex); // 정점1개의 바이트용량
    UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
    //SLOT(레지스터리)
    m_pImmediateContext->IASetVertexBuffers(0, 1,
        &m_pVertexBuffer, &stride, &offset);

    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pShader->m_pVS, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pShader->m_pPS, NULL, 0);

    m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //tex
    //맨 앞 숫자는 pixelshader.txt의 레지스터 번호와 동일해야한다
    ID3D11ShaderResourceView* srv = m_pTexture->GetSRV();
    m_pImmediateContext->PSSetShaderResources(0, 1, &srv);
   
    m_pImmediateContext->Draw(m_VertexList.size(), 0);
    return true;
}

bool		KBaseObject::Release()
{
    m_pTexture->Release();
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pVertexLayout) m_pVertexLayout->Release();
    m_pShader->Release();
    
    return true;
}

