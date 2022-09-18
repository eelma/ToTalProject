#include "KDevice.h"

bool KDevice::Init()
{

    HRESULT hr;
    if (FAILED(hr = CreateGXGIDevice()))
    {
        return false;
    }

    if (FAILED(hr = CreateDevice()))
    {
        return false;
    }

    if (FAILED(hr = CreateSwapChain()))
    {
        return false;
    }
    if (FAILED(hr = CreateRenderTargetView()))
    {
        return false;
    }
    CreateViewport();
    return true;
}

bool KDevice::Frame()
{
    return true;
}

bool KDevice::Render()
{
    //매 프레임마다 우리가 만든 랜더타겟에다가 &m_RTV으로 뿌려라
    m_lmmediateContext->OMSetRenderTargets(1, &m_RTV, NULL);
    float color[4] = { 1.0f,1.0f,1.0f,1.0f };
    m_lmmediateContext->ClearRenderTargetView(m_RTV, color);
    //백버퍼하고 프론트버퍼하고 바꿔라(플립핑)
    m_SwapChain->Present(0, 0);

    return true;
}

bool KDevice::Release()
{
    if (m_d3dDevice) m_d3dDevice->Release();//디바이스 객체
    if (m_lmmediateContext) m_lmmediateContext->Release();
    if (m_GIFactory) m_GIFactory->Release();
    if (m_SwapChain) m_SwapChain->Release();
    if (m_RTV)m_RTV->Release();
    return true;
}



HRESULT KDevice::CreateDevice()
{
    //1)디바이스 생성
    HRESULT hr;
    D3D_FEATURE_LEVEL pFeatureLevel;
    //그래픽카드
    UINT Flags = 0;

    CONST D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };

    UINT FeatureLevels = 1;

    hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION,
        &m_d3dDevice,//디바이스 객체
        &pFeatureLevel,
        &m_lmmediateContext//즉시 컨텍스트

    );

    //m_d3dDevice 다른 인터페이스 생성시 사용한다.
    //m_lmmediateContext 생성된 인터페이스를 사용(관리, 제어)할 때

    //반드시 써야하는 매크로 succeeded or failed만 써라
    return hr;
}

HRESULT KDevice::CreateGXGIDevice()
{
    //2)팩토리 생성
   //IDXGIFactory에 해당하는 아이디를 통해서 객체를 생성한다
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_GIFactory);
    return hr;

}

HRESULT KDevice::CreateSwapChain()
{
    //3)스왑체인 생성
    //후면(백)버퍼 생성->전면 버퍼
    HRESULT hr;

    DXGI_SWAP_CHAIN_DESC sd;

    ZeroMemory(&sd, sizeof(sd));

    sd.BufferCount = 1;
    sd.BufferDesc.Width = g_rtClient.right;
    sd.BufferDesc.Height = g_rtClient.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = g_hWnd;
    sd.Windowed = true;
    //윈도우 기반으로 클라이언트 영역에 띄우겠다

    //주사율
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    hr = m_GIFactory->CreateSwapChain(m_d3dDevice, &sd, &m_SwapChain);
    return hr;
}

HRESULT KDevice::CreateRenderTargetView()
{
    HRESULT hr;
    //4)랜더타겟뷰 생성
   //가로세로로된 이미지
    ID3D11Texture2D* pBackBuffer = nullptr;
    //만들어져 있는 백버퍼에 텍스쳐로 리턴해줘
    m_SwapChain->GetBuffer(0, __uuidof(pBackBuffer), (void**)&pBackBuffer);
    //나는 이 버퍼를 가지고 렌더타겟으로 만들어 쓰겟다
    //dx에서는 get을 하면 복제가 돼서 넘어오기 때문에 랜덤 타겟이라는걸 만들고 난 후엔 릴리즈 시켜준다
    hr = m_d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_RTV);
    pBackBuffer->Release();
    return hr;

}

void KDevice::CreateViewport()
{

    //5)뷰포트 설정
    //백버퍼 크기 그대로 뷰포트 설정해서 붙인것
    D3D11_VIEWPORT vp;
    vp.Width = g_rtClient.right;
    vp.Height = g_rtClient.bottom;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    m_lmmediateContext->RSSetViewports(1, &vp);


}