#pragma once

#include"Std.h"
class KWindow
{
public:
	HINSTANCE m_hlnstance;//������ȣ
	HWND m_hWnd;//�����츦 ������ �� �ִ� �ڵ�( ����ȣ )
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
	virtual bool Init();//�ʱ�ȭ
	virtual bool Frame();//�ǽð� ���
	virtual bool Render();//�ǽð� ������
	virtual bool Release();//�Ҹ� �� ����
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

