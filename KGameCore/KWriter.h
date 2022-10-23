#pragma once 
#include "KStd.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment( lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")
class KWriter
{
public:
	ID2D1Factory*		m_d2dFactory;
	ID2D1RenderTarget*	m_d2dRT;
	IDWriteFactory*		m_pDWriteFactory;
	IDWriteTextFormat*	m_pTextForamat;
	//실시간으로 폰트 변경 불가능
	ID2D1SolidColorBrush* m_pTextColor;
	wstring				m_szDefaultText;

	IDWriteTextLayout* m_pTextLayout;
	//중요한건 아니다 실시간으로 폰트 변경 가능 대신 글자는 못바꿈

public:
	virtual bool		Init(); // 초기화
	virtual bool		Frame();// 실시간 계산
	virtual bool		Render();// 실시간 랜더링
	virtual bool		Release();// 소멸 및 삭제
	virtual HRESULT CreateDXResource();
	virtual HRESULT DeleteDXResource();

public:
	bool Set(IDXGISurface1* dxgiSurface);
	bool		Draw(float x, float y, wstring text, D2D1_COLOR_F color = {0,0,0,1});
};

