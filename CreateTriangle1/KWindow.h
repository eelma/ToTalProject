#pragma once
#include "KStd.h"
class KWindow 
{
public:
	HINSTANCE   m_hInstance;	// ������ȣ
	HWND		m_hWnd;			// ����ȣ
	RECT		m_rtWindow;
	RECT		m_rtClient;
	DWORD       m_csStyle;
	UINT		m_iClientWidth;
	UINT		m_iClientHeight;
	bool		m_bGameRun;
#ifdef _DEBUG
	std::vector<UINT>  msglist;
#endif
public:
	bool		SetWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidth=1024, UINT iHeight=768);
	ATOM		MyRegisterClass();
	BOOL		InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	bool		Run();	
	void		CenterWindow();
public:
	virtual bool		KCoreInit(); // �ʱ�ȭ
	virtual bool		KCoreFrame();// �ǽð� ���
	virtual bool		KCoreRender();// �ǽð� ������
	virtual bool		KCoreRelease();// �Ҹ� �� ����	
	virtual LRESULT		MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	KWindow();
};

