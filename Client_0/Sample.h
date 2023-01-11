#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"KGameCore.h"
#include"NetWork.h"
class Sample:public KGameCore
{

	NetWork m_Net;
	HWND m_hEdit;
	HWND m_hListbox;
	HWND m_hSendBtn;
	bool m_bNameSend = false;
public:
	void Print(const WCHAR* msg, ...);
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)override;
	bool Run() override;
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
};

