#include "KWriter.h"
bool KWriter::Set(IDXGISurface1*dxgiSurface)
{
	//�߿�: ����̽� ���� �÷��� �����ؾ� �Ѵ�
	//     UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	//3d->2d����
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
		L"���"//L"���" L"Gabriola"
		,NULL
		,DWRITE_FONT_WEIGHT_NORMAL
		,DWRITE_FONT_STYLE_NORMAL
		,DWRITE_FONT_STRETCH_NORMAL
		,30
		, L"ko-kr"//L"ko-kr" L"en-us"
		,&m_pTextForamat);
	//����۴� �����Ѵ�

	//m_szDefaultText = L"KGCA Game Academy";

	//hr = m_pDWriteFactory->CreateTextLayout(
	//	m_szDefaultText.c_str()//L"���" L"Gabriola"
	//	, m_szDefaultText.size()
	//	, m_pTextForamat
	//	, g_rtClient.right
	//	,g_rtClient.bottom
	//	, &m_pTextLayout);


	return true;
}

bool KWriter::Frame()
{
	return true;
}

bool KWriter::Render()
{
	Draw(0, 0, m_szDefaultText,{1,1,1,1});
	
	return true;
}
bool KWriter::Draw(float x, float y,wstring text,D2D1_COLOR_F color)
{
	m_d2dRT->BeginDraw();
	//�� ���̿��� �������� �ϸ�ȴ�
	D2D1_RECT_F rt = { x,y,g_rtClient.right,g_rtClient.bottom };
	m_pTextColor->SetColor(color);
	m_pTextColor->SetOpacity(1.0f);
	//m_pTextColor->SetTransform();
	m_d2dRT->DrawText(text.c_str(), text.size(), m_pTextForamat, rt, m_pTextColor);
	//�̰� ����� �Ҷ��� ����
	//������ ä�� �����ϰ� ���� �̹����� ���� �ӵ��� ������ ������
	/*m_pTextLayout->SetFontSize(20, { 0,(UINT)m_szDefaultText.size() });
	m_pTextLayout->SetFontStyle(DWRITE_FONT_STYLE_ITALIC, {0,(UINT)m_szDefaultText.size()});
	m_d2dRT->DrawTextLayout({ (float)g_rtClient.right-m_szDefaultText.size()*20,0}, m_pTextLayout, m_pTextColor);
	*/
	m_d2dRT->EndDraw();
	return true;
}

bool KWriter::Release()
{
	//if (m_pTextLayout)m_pTextLayout->Release();
	if (m_pTextColor)m_pTextColor->Release();
	if (m_pDWriteFactory)m_pDWriteFactory->Release();
	if (m_d2dRT)m_d2dRT->Release();
	if (m_d2dFactory)m_d2dFactory->Release();
	
	return true;
}

HRESULT KWriter::CreateDXResource()
{
	HRESULT hr = m_d2dRT->CreateSolidColorBrush({ 0,0,0,1 }, &m_pTextColor);
	return true;
}

HRESULT KWriter::DeleteDXResource()
{
	if (m_pTextColor)m_pTextColor->Release();
	if (m_d2dRT)m_d2dRT->Release();
	return true;
}
