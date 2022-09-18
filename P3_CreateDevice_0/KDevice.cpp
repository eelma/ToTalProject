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
    //�� �����Ӹ��� �츮�� ���� ����Ÿ�ٿ��ٰ� &m_RTV���� �ѷ���
    m_lmmediateContext->OMSetRenderTargets(1, &m_RTV, NULL);
    float color[4] = { 1.0f,1.0f,1.0f,1.0f };
    m_lmmediateContext->ClearRenderTargetView(m_RTV, color);
    //������ϰ� ����Ʈ�����ϰ� �ٲ��(�ø���)
    m_SwapChain->Present(0, 0);

    return true;
}

bool KDevice::Release()
{
    if (m_d3dDevice) m_d3dDevice->Release();//����̽� ��ü
    if (m_lmmediateContext) m_lmmediateContext->Release();
    if (m_GIFactory) m_GIFactory->Release();
    if (m_SwapChain) m_SwapChain->Release();
    if (m_RTV)m_RTV->Release();
    return true;
}



HRESULT KDevice::CreateDevice()
{
    //1)����̽� ����
    HRESULT hr;
    D3D_FEATURE_LEVEL pFeatureLevel;
    //�׷���ī��
    UINT Flags = 0;

    CONST D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };

    UINT FeatureLevels = 1;

    hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION,
        &m_d3dDevice,//����̽� ��ü
        &pFeatureLevel,
        &m_lmmediateContext//��� ���ؽ�Ʈ

    );

    //m_d3dDevice �ٸ� �������̽� ������ ����Ѵ�.
    //m_lmmediateContext ������ �������̽��� ���(����, ����)�� ��

    //�ݵ�� ����ϴ� ��ũ�� succeeded or failed�� ���
    return hr;
}

HRESULT KDevice::CreateGXGIDevice()
{
    //2)���丮 ����
   //IDXGIFactory�� �ش��ϴ� ���̵� ���ؼ� ��ü�� �����Ѵ�
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_GIFactory);
    return hr;

}

HRESULT KDevice::CreateSwapChain()
{
    //3)����ü�� ����
    //�ĸ�(��)���� ����->���� ����
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
    //������ ������� Ŭ���̾�Ʈ ������ ���ڴ�

    //�ֻ���
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
    //4)����Ÿ�ٺ� ����
   //���μ��ηε� �̹���
    ID3D11Texture2D* pBackBuffer = nullptr;
    //������� �ִ� ����ۿ� �ؽ��ķ� ��������
    m_SwapChain->GetBuffer(0, __uuidof(pBackBuffer), (void**)&pBackBuffer);
    //���� �� ���۸� ������ ����Ÿ������ ����� ���ٴ�
    //dx������ get�� �ϸ� ������ �ż� �Ѿ���� ������ ���� Ÿ���̶�°� ����� �� �Ŀ� ������ �����ش�
    hr = m_d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_RTV);
    pBackBuffer->Release();
    return hr;

}

void KDevice::CreateViewport()
{

    //5)����Ʈ ����
    //����� ũ�� �״�� ����Ʈ �����ؼ� ���ΰ�
    D3D11_VIEWPORT vp;
    vp.Width = g_rtClient.right;
    vp.Height = g_rtClient.bottom;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    m_lmmediateContext->RSSetViewports(1, &vp);


}