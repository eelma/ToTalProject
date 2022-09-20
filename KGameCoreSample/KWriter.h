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
	ID2D1SolidColorBrush* m_pTextColor;
	wstring				m_szDefaultText;

public:
	virtual bool		Init(); // 초기화
	virtual bool		Frame();// 실시간 계산
	virtual bool		Render();// 실시간 랜더링
	virtual bool		Release();// 소멸 및 삭제
public:
	bool Set(IDXGISurface1* dxgiSurface);
};

