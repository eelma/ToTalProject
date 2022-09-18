#pragma once

#include"Std.h"
class KWindow
{
public:
	HINSTANCE m_hlnstance;//접수번호
	HWND m_hWnd;//윈도우를 제어할 수 있는 핸들( 등기번호 )
	RECT m_rtWindow;
	RECT m_rtClient;
	DWORD m_csStyle;
	UINT m_iClientWidht;
	UINT m_iClientHeight;

#ifdef _DEBUG
	vector<UINT>msglist;
#endif // DEBUG


public:
	bool SetWindow(HINSTANCE hlnstance, const WCHAR* szTitle, UINT iWidth = 1024, UINT iHeight = 768);
	ATOM MyRegisterClass();
	BOOL InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	bool Run();
	void CenterWindow();
	KWindow();

public:
	virtual bool Init();//초기화
	virtual bool Frame();//실시간 계산
	virtual bool Render();//실시간 렌더링
	virtual bool Release();//소멸 및 삭제
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

