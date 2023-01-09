//파일디스크립터:네트워크 소켓과 같은 파일이나 기타 입력/출력 리소스에 액세스하는 데 사용되는 추상표현이다. 즉, 시스템으로 부터 할당받은 파일이나 소켓을 대표하는 정수다.
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include"CliProtocol.h"
int SendMsg(SOCKET sock, char* msg, short type)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(UPACKET));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg,msg, strlen(msg));

	char* msgSend = (char*)&packet;
	int iSendBytes = send(sock, msgSend, packet.ph.len, 0);
	if (iSendBytes == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			closesocket(sock);
			return -1;
		}
	}
	return 1;
}
DWORD WINAPI SendThread(LPVOID IpThreadParameter)
{
	SOCKET sock = (SOCKET)IpThreadParameter;
	while (1)
	{

		char szSendMsg[256] = { 0, };
		printf("%s", "send----->");
		fgets(szSendMsg, 256,stdin);
		szSendMsg[strlen(szSendMsg) - 1] = 0;
		if (strcmp(szSendMsg, "exit") == 0)
		{
			break;
		}
		if (SendMsg(sock, szSendMsg, PACKET_CHAR_MSG) < 0)
		{
			break;
		}
	}
};

int main()
{
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws))
	{
		return 1;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	sa.sin_addr.s_addr = inet_addr("192.168.0.86");
	sa.sin_port = htons(10000);
	sa.sin_family = AF_INET;

	int iRet = connect(sock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		int iError = WSAGetLastError();
		printf("%d", iError);
		return 1;
	}
	DWORD dwThreadID;
	HANDLE hClient = CreateThread(0,0,SendThread,(LPVOID)sock, 0, &dwThreadID);

	//u_long iMode = TRUE;
	//ioctlsocket(sock, FIONBIO, &iMode);
	
	int iRecvPacketSize = PACKET_HEADER_SIZE;
	int iTotalRecvBytes = 0;

	while (1)
	{

		Sleep(100);
		char szRecvMsg[256] = { 0, };
		int iRecvBytes = recv(sock, szRecvMsg, PACKET_HEADER_SIZE-iTotalRecvBytes, 0);
		if (iRecvBytes == 0)
		{
			printf("서버 정상종료\n");
			break;
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
				int iRecvBytes = recv(sock, &packet.msg[iNumRecvByte], packet.ph.len-PACKET_HEADER_SIZE,0);
			
		
			if (iRecvBytes == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					closesocket(sock);
					printf("서버 비정상 종료\n");
					return 1;
				}
			continue;
		}
			iNumRecvByte += iRecvBytes;
		} while ((packet.ph.len - PACKET_HEADER_SIZE)>iNumRecvByte);

		switch (packet.ph.type)
		{
		case PACKET_CHAR_MSG:
			{
				printf("Recv---->%s\n", packet.msg);
			}break;
		}
		iTotalRecvBytes = 0;
		}
	}
	CloseHandle(hClient);
	closesocket(sock);
	WSACleanup();
	Sleep(500);
	return 0;

}