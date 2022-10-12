#pragma once
#include"mStd.h"
class mWindow
{
public:
	HINSTANCE m_hInstance;//접수번호
	HWND m_hWnd; //등기번호
	RECT m_rtWindopw;
	RECT m_rtClient;
	DWORD m_csStyle;
	UINT m_iClientWith;
	UINT m_iClientHeight;

public:
	bool SetWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidht = 1024, UINT iHeight = 768);
	ATOM MyRegisterClass();
	BOOL InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	virtual bool RUN();
	void CenterWindow();

public:
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam);
public:
	mWindow();
};

