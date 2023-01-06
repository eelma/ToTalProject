//파일디스크립터:네트워크 소켓과 같은 파일이나 기타 입력/출력 리소스에 액세스하는 데 사용되는 추상표현이다. 즉, 시스템으로 부터 할당받은 파일이나 소켓을 대표하는 정수다.
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include"CliProtocol.h"
DWORD WINAPI SendThread(LPVOID IpThreadParameter)
{
	SOCKET sock = (SOCKET)IpThreadParameter;
	while (1)
	{

		char szSendMsg[256] = { 0, };
		printf("%s", "send----->");
		fgets(szSendMsg, 256,stdin);
		int iSendBytes = send(sock, szSendMsg, strlen(szSendMsg), 0);
		if (iSendBytes == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(sock);
				return 1;
			}
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

	DWORD iMode = TRUE;
	ioctlsocket(sock, FIONBIO, &iMode);
	int count = 0;
	while (1)
	{

		Sleep(10);
		char szRecvMsg[256] = { 0, };
		int iRecvBytes = recv(sock, szRecvMsg, 256, 0);
		if (iRecvBytes == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(sock);
				return 1;
			}
			continue;
		}
		printf("Recv---->%s\n", szRecvMsg);
	}
	CloseHandle(hClient);
	closesocket(sock);
	WSACleanup();
	return 0;

}