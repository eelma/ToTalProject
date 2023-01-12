#include "Sample.h"
void Sample::RecvThread()
{

	NetWork* net = (NetWork*)&m_Net;
	SOCKET sock = net->m_Sock;
	int iRecvPacketSize = PACKET_HEADER_SIZE;
	int iTotalRecvBytes = 0;
	while (1)
	{
		char szRecvMsg[256] = { 0, };
		int iRecvBytes = recv(net->m_Sock, szRecvMsg, PACKET_HEADER_SIZE - iTotalRecvBytes, 0);
		if (iRecvBytes == 0)
		{
			printf("서버 정상 종료\n");
			return;
		}
		if (iRecvBytes == SOCKET_ERROR)
		{

			printf("비정상 반환\n");
			return;
		}
		iTotalRecvBytes += iRecvBytes;
		if (iTotalRecvBytes == PACKET_HEADER_SIZE)
		{

			UPACKET packet;
			ZeroMemory(&packet, sizeof(UPACKET));
			memcpy(&packet.ph, szRecvMsg, PACKET_HEADER_SIZE);

			char* msg = (char*)&packet;
			int iNumRecvByte = 0;
			do {
				if (packet.ph.len == 4)
				{
					break;
				}
				int iRecvBytes = recv(net->m_Sock, &packet.msg[iNumRecvByte], packet.ph.len - PACKET_HEADER_SIZE - iNumRecvByte,0);

				if (iRecvBytes == 0)
				{
					printf("서버 정상 종료\n");
					break;
				}
				if (iRecvBytes == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						closesocket(net->m_Sock);
						printf("비정상 종료\n");
						return;
					}
					continue;
				}
				iNumRecvByte += iRecvBytes;
			} while ((packet.ph.len - PACKET_HEADER_SIZE) > iNumRecvByte);

			net->m_PacketList.push_back(packet);
			iTotalRecvBytes = 0;
			return;
		}
	}

}
bool Sample::Init()
{
	wstring fmt = L"IP[%s]: PORT[%d]: %s";
	if (m_Net.NetStart("192.168.0.86", 10000))
	{
		Print(fmt.c_str(), L"192.168.0.86", 10000, L"접속 성공");
	}
	else
	{
		Print(fmt.c_str(), L"192.168.0.86",10000, L"접속 실패");
	}
	return true;
}
bool Sample::Render()
{
	m_Net.Render();
	return true;
}
void Sample::NetProcess()
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
			Print(fmt.c_str(), L"이름을 입력하시오 : ");

		}break;
		case PACKET_JOIN_USER:
		{
			wstring fmt = L"%s%s";
			Print(fmt.c_str(),to_mw(packet.msg).c_str(), L"님이 입장하였습니다");
		}break;

		case PACKET_NAME_ACK:
		{
			wstring fmt =L"%s%s";
			Print(fmt.c_str(), to_mw(packet.msg).c_str(), L"대화명 사용 승인");

		}break;
		}
	}
	m_Net.m_PacketList.clear();

	m_Net.Render();

}
bool Sample::Frame()
{

	m_Net.Frame();
	NetProcess();
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
	case NETWORK_MSG:
	{
		if (WSAGETSELECTERROR(IParam) != 0)
		{
			PostQuitMessage(0);
			break;
		}
		WORD dwSelect = WSAGETSELECTEVENT(IParam);
		switch (dwSelect)
		{
		case FD_CONNECT:
		{
			int t = 0;
		}break;
		case FD_READ:
		{
			
		}break;
		case FD_WRITE:
		{
			int t = 0;
		}break;
		case FD_CLOSE:
		{
			int t = 0;
		}break;
		}
	}break;
	case WM_CREATE:
	{
		m_hEdit = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 10, 200, 25, hWnd, (HMENU)1000, m_hInstance, NULL);
		
		m_hSendBtn = CreateWindow(L"button", L"Send", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 700, 10, 50, 25, hWnd, (HMENU)1001, m_hInstance, NULL);
		
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