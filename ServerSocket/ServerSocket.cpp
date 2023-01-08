//파일디스크립터:네트워크 소켓과 같은 파일이나 기타 입력/출력 리소스에 액세스하는 데 사용되는 추상표현이다. 즉, 시스템으로 부터 할당받은 파일이나 소켓을 대표하는 정수다.
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include"ServProtocol.h"
DWORD WINAPI ServerThread(LPVOID IpThreadParameter)
{
	
	while (1)
	{
		for (auto iterRecv = userlist.begin(); userlist.end() != iterRecv;)
		{
			char szRecvMsg[256] = { 0, };
			int iRecvBytes = recv(iterRecv->sock, szRecvMsg, 256, 0);
			if (iRecvBytes == 0)
			{
				printf("클라이언트 접속 종료 : IP:%s, PORT:%d\n", inet_ntoa(iterRecv->address.sin_addr), htons(iterRecv->address.sin_port));
				closesocket(iterRecv->sock);
				iterRecv = userlist.erase(iterRecv);
				continue;
			}
			if (iRecvBytes == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					closesocket(iterRecv->sock);
					iterRecv = userlist.erase(iterRecv);
					continue;
				}
			}
			if (iRecvBytes > 0)
			{
				printf("%s\n", szRecvMsg);
				for (auto iterSend = userlist.begin();userlist.end() != iterSend;)
				{

					int iSendBytes = send(iterSend->sock, szRecvMsg, strlen(szRecvMsg), 0);
					if (iSendBytes == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("클라이언트 비정상 종료 IP: %s, PROT: %d\n", inet_ntoa(iterSend->address.sin_addr), ntohs(iterSend->address.sin_port));
							closesocket(iterSend->sock);
							iterSend = userlist.erase(iterSend);
							continue;
						}
					}
					iterSend++;
				}
			}
			iterRecv++;
		}
	}
};

int main()
{
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		return 0;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(10000);
	sa.sin_family = AF_INET;
	int iRet = bind(sock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return 1;
	}
	iRet = listen(sock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
	{
		return 1;
	}

	DWORD dwThread;
	HANDLE hClient = CreateThread(0, 0, ServerThread, 0, 0, &dwThread);
	
	while (1)
	{
		SOCKADDR_IN clientaddr;
		int length = sizeof(clientaddr);
		SOCKET clientSock = accept(sock, (sockaddr*)&clientaddr, &length);

		if (clientSock == SOCKET_ERROR)
		{
			closesocket(sock);
			WSACleanup();
			return 1;
		}
		printf("클라이언트 접속 : IP:%s PORT: %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		u_long iMode = TRUE;
		ioctlsocket(clientSock, FIONBIO, &iMode);

		User user;
		user.sock = clientSock;
		user.address = clientaddr;
		userlist.push_back(user);

		
		
		
	}
	closesocket(sock);

	WSACleanup();

	return 0;
}
