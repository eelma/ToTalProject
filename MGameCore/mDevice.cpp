#include "mDevice.h"
HRESULT mDevice::CreateDXResource()
{
	return true;
}
HRESULT mDevice::DeleteDXResource()
{
	return true;
}


HRESULT mDevice::ResizeDevice(UINT width, UINT height)
{
	HRESULT hr;
	//������ ũ�� ���� �޽��� ����(WM_SIZE)
	if (m_pd3dDevice == nullptr)return S_OK;
	
	//���� ������ ����Ÿ�� ���� �� �Ҹ�
	DeleteDXResource();
	
	//0 ->����Ÿ���� ��
	//nullptr-> ����Ÿ�ٺ��� �迭 null�� �ѱ�� ���� Ÿ���� �������� �ʰԵȴ�
	//null-> null�� �ѱ�� ���� ���ٽ� ���۴� �������� ����
	m_pImmediateContext->OMSetRenderTargets(0, nullptr, NULL);
	m_pRTV.ReleaseAndGetAddressOf();
	//����� �������� ũ�⸦ ��� �� ������ ũ�⸦ �� ����.
	DXGI_SWAP_CHAIN_DESC CurrentSD, AfterSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	hr = m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, width, height,
		CurrentSD.BufferDesc.Format, 0);

	//����� �� ������ ũ�⸦ ��� ����Ÿ�� �並 �ٽ� ���� �� ����
	//����Ʈ �� ����
	if (FAILED(hr = CreateRenderTargetView()))
	{
		return false;
	}
	CreateViewport();
	CreateDXResource();
	return S_OK;
}

bool mDevice::Init()
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
bool mDevice::Frame()
{
	return true;
}
bool mDevice::Render()
{
	return true;
}
bool mDevice::Release()
{
	if (m_pd3dDevice)m_pd3dDevice->Release();
	if (m_pImmediateContext)m_pImmediateContext->Release();
	if (m_pGIFactory)m_pGIFactory->Release();
	if (m_pSwapChain)m_pSwapChain->Release();
	if (m_pRTV)m_pRTV->Release();
	return true;
}

HRESULT mDevice::CreateDevice()
{
	HRESULT hr;

	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef  _DEBUG
	//����� �ɼ��� �־�� ����� ������ ����
	//�̰� �־�� ����Ÿ���� �����ȴ�
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif //  _DEBUG

	D3D_FEATURE_LEVEL pFeatureLevel;
	D3D_FEATURE_LEVEL pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
	};
	UINT FeatureLevels = 1;
	//���÷��� ����͸� ��Ÿ���� ��ġ�� ����ϴ�.
	hr = D3D11CreateDevice(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL,
		createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION,
		&m_pd3dDevice,
		&pFeatureLevel,
		&m_pImmediateContext
	);//���� https://m.blog.naver.com/gksqufrnt/220876969326

	return hr;
}

HRESULT mDevice::CreateDXGIDevice()
{
	//2. ���丮 ����
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);
	return hr;
}

HRESULT mDevice::CreateSwapChain()
{
	//3.����ü�� ����
	//�ĸ�(��)���� ����->������۷� ��Ȳ
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;

	//BufferDesc ����� ǥ�� ��带 ���� �ϴ� DXGI_MODE_DESC �����Դϴ�.
	sd.BufferDesc.Width = g_rtClient.right;
	sd.BufferDesc.Height = g_rtClient.bottom;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//BufferUsage �� ���ۿ� ���� ǥ�� ��뷮 �� CPU �׼��� �ɼ��� �����ϴ� DXGI_USAGE ���� ���� �� ����Դϴ� . �� ���۴� ���̴� �Է� �Ǵ� ���� ��� ��¿� ����� �� �ֽ��ϴ�.
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//OutputWindow ��� â�� ���� HWND �ڵ��Դϴ�. �� ����� NULL �� �ƴϾ�� �մϴ� .
	sd.OutputWindow = g_hWnd;

	//Windowed ����� â ������� ���θ� �����ϴ� �ο� ���Դϴ�. ����� â ����� ��� TRUE �Դϴ�. �׷��� ������ FALSE .
	sd.Windowed = true;

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	//SampleDesc ���� ���ø� �Ű������� ���� �ϴ� DXGI_SAMPLE_DESC �����Դϴ�.
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	//Flags ���� ü�� ���ۿ� ���� �ɼ��� �����ϴ� DXGI_SWAP_CHAIN_FLAG ���� ���� �� ����Դϴ� .
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	return m_pGIFactory->CreateSwapChain(m_pd3dDevice.Get(), &sd, &m_pSwapChain);

}
HRESULT mDevice::CreateRenderTargetView()
{
	HRESULT hr;
	ID3D11Texture2D* pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)& pBackBuffer);
	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);
	pBackBuffer->Release();
	return hr;
}

void mDevice::CreateViewport()
{
	//5. ����Ʈ ����
	D3D11_VIEWPORT vp;
	vp.Width = g_rtClient.right;
	vp.Height = g_rtClient.bottom;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &vp);
}