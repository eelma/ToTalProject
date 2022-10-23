#include "KDevice.h"
bool		KDevice::Init()
{ 
    HRESULT hr;
    if (FAILED(hr = CreateDXGIDevice()))
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
bool		KDevice::Frame()
{
    return true;
}
bool		KDevice::Render()
{  
    return true;
}
bool		KDevice::Release()
{
    //if (m_pd3dDevice) m_pd3dDevice->Release();// ����̽� ��ü        
    //if (m_pImmediateContext)m_pImmediateContext->Release();
    //if (m_pGIFactory)m_pGIFactory->Release();
    //if (m_pSwapChain)m_pSwapChain->Release();
    //if (m_pRTV) m_pRTV->Release();
    return true;
}


HRESULT KDevice::CreateDevice()
{
    // 1)����̽� ����
    HRESULT hr;

    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    //����� �ɼ��� �־���� ����� ������ �������ش�
    //�̰� �־�߸� ����Ÿ���� �����̵ȴ�
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL pFeatureLevel;
    D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT FeatureLevels = 1;
    hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL,
        createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION,
        &m_pd3dDevice,// ����̽� ��ü
        &pFeatureLevel,
        &m_pImmediateContext
    );

    //m_pd3dDevice  �ٸ� �������̽� ������ ����Ѵ�.
    //m_pImmediateContext ������ �������̽��� ���(����,����)�� ��.
    return hr;
}

HRESULT KDevice::CreateDXGIDevice()
{
    // 2)���丮 ����
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);
    return hr;
}

HRESULT KDevice::CreateSwapChain( )
{
    // 3)����ü�� ����
    // �ĸ�(��)���� ����  -> �������
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width  = g_rtClient.right;
    sd.BufferDesc.Height = g_rtClient.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = g_hWnd;
    sd.Windowed = true;

    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    return m_pGIFactory->CreateSwapChain(m_pd3dDevice.Get(), &sd, &m_pSwapChain);
}

HRESULT KDevice::CreateRenderTargetView()
{
    HRESULT hr;
    // 4)����Ÿ�Ϻ� ����
    ID3D11Texture2D* pBackBuffer = nullptr;
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);
    pBackBuffer->Release();
    return hr;
}

HRESULT KDevice::CreateDepthStencilView()
{
    HRESULT hr;
    D3D11_RENDER_TARGET_VIEW_DESC rtvd;
    m_pRTV->GetDesc(&rtvd);
    DXGI_SWAP_CHAIN_DESC scd;
    m_pSwapChain->GetDesc(&scd);

       //1�� �ؽ�ó�� �����Ѵ�
    ComPtr<ID3D11Texture2D> pDSTexture;
    D3D11_TEXTURE2D_DESC td;
    td.Width = scd.BufferDesc.Width;
    td.Height = scd.BufferDesc.Height;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    td.SampleDesc.Count = 1;
    td.SampleDesc.Quality = 0;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    td.CPUAccessFlags = 0;
    td.MiscFlags = 0;
    
    hr = m_pd3dDevice->CreateTexture2D(&td, NULL, pDSTexture.GetAddressOf());
       //2�� �̰ɷ� ���� ���ٽ� ��� �����Ѵ�
    D3D11_DEPTH_STENCIL_VIEW_DESC dtvd;
    ZeroMemory(&dtvd, sizeof(dtvd));
    dtvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dtvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    hr = m_pd3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dtvd, m_pDepthStencilView.GetAddressOf());
       //�츮�� ���۵� ������� ����°� ���� ä��°� ���δ�
       //�츮�� �ؽ��ĸ� �����Ҷ� ä�� ������ ���� ���� �������ҰŶ�
       //3�� �� ����
       //4�� ���̽��ٽ� �� ���� ��ü �����ؼ� ����

   return hr;
}

void KDevice::CreateViewport()
{
    // 5)����Ʈ ����
    //Ŭ���̾�Ʈ ������ �ѷ���
    
    m_vp.Width  = g_rtClient.right;
    m_vp.Height = g_rtClient.bottom;
    m_vp.TopLeftX = 0;
    m_vp.TopLeftY = 0;
    m_vp.MinDepth = 0.0f;
    m_vp.MaxDepth = 1.0f;
    m_pImmediateContext->RSSetViewports(1, &m_vp);
}

HRESULT KDevice::ResizeDevice(UINT width, UINT height)
{
    HRESULT hr;
    //������ ũ�� ���� �޽��� ����(WM_SIZE)
    if (m_pd3dDevice == nullptr)return S_OK;
    //���� ������ ����Ÿ�� ���� �� �Ҹ�
    DeleteDXResource();
    //�ϳ� �̻��� ���� Ÿ���� ���������� ���ε��ϰ� ���� ���ٽ� ���۸� output-merger ���������� ���ε� �մϴ�.
    m_pImmediateContext->OMSetRenderTargets(0, nullptr, NULL);
    m_pRTV.ReleaseAndGetAddressOf();
    //����� �������� ũ�⸦ ��� ������� ũ�⸦ �� ����.
    //������� ũ�⸦ �����Ѵ�.
    DXGI_SWAP_CHAIN_DESC CurrentSD, AfterSD;
    m_pSwapChain->GetDesc(&CurrentSD);
    hr = m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, width, height, CurrentSD.BufferDesc.Format, 0);
    // ����� �� ������ ũ�⸦ ��� ����Ÿ�� �並 �ٽ� ���� ������.
    //����Ʈ ������.
    if (FAILED(hr = CreateRenderTargetView()))
    {
        return false;
    }
    CreateViewport();

    CreateDXResource();
    return S_OK;
}

HRESULT KDevice::CreateDXResource()
{
    return true;
}

HRESULT KDevice::DeleteDXResource()
{
    return true;
}
