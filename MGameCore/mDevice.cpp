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
	//윈도우 크기 변경 메시지 검출(WM_SIZE)
	if (m_pd3dDevice == nullptr)return S_OK;
	
	//현재 설정된 랜더타켓 해제 및 소멸
	DeleteDXResource();
	
	//0 ->랜더타겟의 수
	//nullptr-> 랜더타겟뷰의 배열 null을 넘기면 랜더 타겟이 설정되지 않게된다
	//null-> null을 넘기면 깊이 스텐실 버퍼는 설정하지 않음
	m_pImmediateContext->OMSetRenderTargets(0, nullptr, NULL);
	m_pRTV.ReleaseAndGetAddressOf();
	//변경된 윈도우의 크기를 얻고 백 버퍼의 크기를 재 조정.
	DXGI_SWAP_CHAIN_DESC CurrentSD, AfterSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	hr = m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, width, height,
		CurrentSD.BufferDesc.Format, 0);

	//변경된 백 버퍼의 크기를 얻고 렌더타켓 뷰를 다시 생성 및 적용
	//뷰포트 재 지정
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
	//디버그 옵션을 넣어야 디버깅 정보를 제공
	//이게 있어야 랜더타겟이 지원된다
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif //  _DEBUG

	D3D_FEATURE_LEVEL pFeatureLevel;
	D3D_FEATURE_LEVEL pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
	};
	UINT FeatureLevels = 1;
	//디스플레이 어댑터를 나타내는 장치를 만듭니다.
	hr = D3D11CreateDevice(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL,
		createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION,
		&m_pd3dDevice,
		&pFeatureLevel,
		&m_pImmediateContext
	);//설명 https://m.blog.naver.com/gksqufrnt/220876969326

	return hr;
}

HRESULT mDevice::CreateDXGIDevice()
{
	//2. 팩토리 생성
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);
	return hr;
}

HRESULT mDevice::CreateSwapChain()
{
	//3.스왑체인 생성
	//후면(백)버퍼 생성->전면버퍼로 전황
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;

	//BufferDesc 백버퍼 표시 모드를 설명 하는 DXGI_MODE_DESC 구조입니다.
	sd.BufferDesc.Width = g_rtClient.right;
	sd.BufferDesc.Height = g_rtClient.bottom;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//BufferUsage 백 버퍼에 대한 표면 사용량 및 CPU 액세스 옵션을 설명하는 DXGI_USAGE 열거 유형 의 멤버입니다 . 백 버퍼는 셰이더 입력 또는 렌더 대상 출력에 사용할 수 있습니다.
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//OutputWindow 출력 창에 대한 HWND 핸들입니다. 이 멤버는 NULL 이 아니어야 합니다 .
	sd.OutputWindow = g_hWnd;

	//Windowed 출력이 창 모드인지 여부를 지정하는 부울 값입니다. 출력이 창 모드인 경우 TRUE 입니다. 그렇지 않으면 FALSE .
	sd.Windowed = true;

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	//SampleDesc 다중 샘플링 매개변수를 설명 하는 DXGI_SAMPLE_DESC 구조입니다.
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	//Flags 스왑 체인 동작에 대한 옵션을 설명하는 DXGI_SWAP_CHAIN_FLAG 열거 유형 의 멤버입니다 .
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
	//5. 뷰포트 설정
	D3D11_VIEWPORT vp;
	vp.Width = g_rtClient.right;
	vp.Height = g_rtClient.bottom;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &vp);
}