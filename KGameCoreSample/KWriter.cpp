#include "KWriter.h"
bool KWriter::Set(IDXGISurface1*dxgiSurface)
{
	//중요: 디바이스 생성 플래그 지정해야 한다
	//     UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	//3d->2d연동
	D2D1_RENDER_TARGET_PROPERTIES props;
	ZeroMemory(&props, sizeof(props));
	props.type= D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat=D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN,D2D1_ALPHA_MODE_PREMULTIPLIED);
	props.dpiX=96;
	props.dpiY=96 ;
	props.usage= D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel= D2D1_FEATURE_LEVEL_DEFAULT;

	HRESULT hr=m_d2dFactory->CreateDxgiSurfaceRenderTarget(
		dxgiSurface,
		&props,
		&m_d2dRT);

	hr=m_d2dRT->CreateSolidColorBrush({0,0,0,1},&m_pTextColor);
	
	return true;
}
bool KWriter::Init()
{
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2dFactory);
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),
		(IUnknown**)&m_pDWriteFactory);
	hr=m_pDWriteFactory->CreateTextFormat(
		L"고딕"//L"고딕" L"Gabriola"
		,NULL
		,DWRITE_FONT_WEIGHT_NORMAL
		,DWRITE_FONT_STYLE_NORMAL
		,DWRITE_FONT_STRETCH_NORMAL
		,50
		, L"ko-kr"//L"ko-kr" L"en-us"
		,&m_pTextForamat);
	//백버퍼는 연동한다

	wstring m_szDefaultText = L"KGCA Game Academy";

	return true;
}

bool KWriter::Frame()
{
	return true;
}

bool KWriter::Render()
{
	m_d2dRT->BeginDraw();
	//이 사이에서 랜더링을 하면된다
	D2D1_RECT_F rt={0,0,1024,768};
	m_pTextColor->SetColor({0,1,0,1});
	m_pTextColor->SetOpacity(1.0f);
	//m_pTextColor->SetTransform();
	m_d2dRT->DrawText(m_szDefaultText.c_str(), m_szDefaultText.size(),m_pTextForamat, rt, m_pTextColor);
	m_d2dRT->EndDraw();
	return true;
}

bool KWriter::Release()
{
	if (m_pDWriteFactory)m_pDWriteFactory->Release();
	if (m_d2dRT)m_d2dRT->Release();
	if (m_d2dFactory)m_d2dFactory->Release();
	
	return true;
}
