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
	virtual bool		Init(); // �ʱ�ȭ
	virtual bool		Frame();// �ǽð� ���
	virtual bool		Render();// �ǽð� ������
	virtual bool		Release();// �Ҹ� �� ����
public:
	bool Set(IDXGISurface1* dxgiSurface);
};

