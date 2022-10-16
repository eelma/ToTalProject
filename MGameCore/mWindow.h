#pragma once
#include"mStd.h"
class mWindow
{
public:
	HINSTANCE m_hInstance;//������ȣ
	HWND m_hWnd; //����ȣ
	RECT m_rtWindow;
	RECT m_rtClient;
	DWORD m_csStyle;
	UINT m_iClientWidth;
	UINT m_iClientHeight;

public:
	bool SetWindow(HINSTANCE hInstance, const WCHAR* szTitle, UINT iWidht, UINT iHeight);
	ATOM MyRegisterClass();
	BOOL InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	virtual bool Run();
	void CenterWindow();

public:
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam);
public:
	mWindow();
};

