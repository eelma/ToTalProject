#include "Sample.h"
bool Sample::Init()
{
	wstring fmt = L"IP[%s]: PORT[%d]: %s";
	if (m_Net.NetStart("192,168..86", 10000))
	{

		Print(fmt.c_str(), L"192.168.0.86", 10000, L"접속 성공");

	}
	else
	{

		Print(fmt.c_str(), L"192.168.0.86",10000, L"접속 실패");
	}
	return true;
}
bool Sample::Frame()
{
	m_Net.Frame();
	return true;
}
bool Sample::Render()
{
	for (auto& packet : m_Net.m_PacketList)
	{

		switch (packet.ph.type)
		{
		case PACKET_CHAR_MSG:
		{
			wstring fmt = L"%s";
			Print(fmt.c_str(), to_mw(packet.msg).c_str());
		}break;

		case PACKET_CHATNAME_REQ:
		{
			wstring fmt = L"%s";
			Print(fmt.c_str(), to_mw(packet.msg).c_str());
		}break;
		case PACKET_JOIN_USER:
		{
			printf("%s %s\n", packet.msg, "님이 입장하였습니다");
		}break;
		case PACKET_NAME_ACK:
		{
			printf("대화명 사용 승인");

		}break;
		}
	}
	m_Net.m_PacketList.clear();

	m_Net.Render();

	return true;
}
bool Sample::Release()
{
	m_Net.Release();
	return true;
}
void Sample::Print(const WCHAR* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	WCHAR msg[256] = L"";
	_vsntprintf(msg, 256, fmt, arg);
	SendMessage(m_hListbox, LB_ADDSTRING, 0, (LPARAM)msg);
	va_end(arg);
}
LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		m_hEdit = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 10, 200, 25, hWnd, (HMENU)1000, m_hInstance, NULL);
		
		m_hSendBtn = CreateWindow(L"button", L"Semd", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 700, 10, 50, 25, hWnd, (HMENU)1001, m_hInstance, NULL);
		
		m_hListbox = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL, 0, 0, 500, 600, hWnd, (HMENU)1002, m_hInstance, NULL);
		
		wstring fmt = L"%s";
		
		Print(fmt.c_str(), L"Chatting start");
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1001:
		{
			WCHAR szBuffer[255] = L"";
			GetWindowText(m_hEdit, szBuffer, 255);
			OutputDebugString(szBuffer);
			if (m_bNameSend == false)
			{
				m_Net.SendMsg(m_Net.m_Sock, to_wm(szBuffer).c_str(), PACKET_NAME_REQ);
				m_bNameSend = true;
			}
			else
			{

				m_Net.SendMsg(m_Net.m_Sock, to_wm(szBuffer).c_str(), PACKET_CHAR_MSG);

			}
		}break;
		}
	}break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, IParam);
}
bool Sample::Run()
{
	Init();
	while (bGameRun)
	{
		if (KWindow::Run() == true)
		{
			Frame();
			Render();
		}
		else
		{
			bGameRun = false;
		}
	}
	Release();
	return true;
}

GAME_RUN(SOCKETWin, 800,600)