#include "KWriter.h"
bool KWriter::Set(IDXGISurface1*dxgiSurface)
{
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
		L"°íµñ"
		,NULL
		,DWRITE_FONT_WEIGHT_NORMAL
		,DWRITE_FONT_STYLE_NORMAL
		,DWRITE_FONT_STRETCH_NORMAL
		,50
		, L"ko-kr"
		,&m_pTextForamat);

	m_szDefaultText = L"KGCA Game Academy";

	return true;
}

bool KWriter::Frame()
{
	return true;
}

bool KWriter::Render()
{
	Draw(0, 0, m_szDefaultText,{1,0,0,1});
	
	return true;
}
bool KWriter::Draw(float x, float y,wstring text,D2D1_COLOR_F color)
{
	m_d2dRT->BeginDraw();
	D2D1_RECT_F rt = { x,y,g_rtClient.right,g_rtClient.bottom };
	m_pTextColor->SetColor(color);
	m_pTextColor->SetOpacity(1.0f);
	m_d2dRT->DrawText(text.c_str(), text.size(), m_pTextForamat, rt, m_pTextColor);
	m_d2dRT->EndDraw();
	return true;
}

bool KWriter::Release()
{
	if (m_pTextColor)m_pTextColor->Release();
	if (m_pDWriteFactory)m_pDWriteFactory->Release();
	if (m_d2dRT)m_d2dRT->Release();
	if (m_d2dFactory)m_d2dFactory->Release();
	
	return true;
}
