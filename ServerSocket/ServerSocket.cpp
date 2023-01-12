//파일디스크립터:네트워크 소켓과 같은 파일이나 기타 입력/출력 리소스에 액세스하는 데 사용되는 추상표현이다. 즉, 시스템으로 부터 할당받은 파일이나 소켓을 대표하는 정수다.
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include"ServProtocol.h"

int SendMsg(SOCKET sock, char* msg, short type)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));

	if (msg != nullptr)
	{
		packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
		memcpy(packet.msg,msg, strlen(msg));
	}
	else
	{
		packet.ph.len = PACKET_HEADER_SIZE;
	}
	packet.ph.type = type;

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

DWORD WINAPI ServerThread(LPVOID IpThreadParameter)
{
	
	while (1)
	{
		for (auto iterRecv = userlist.begin(); userlist.end() != iterRecv;)
		{
			int iRecvPacketSize = PACKET_HEADER_SIZE;
			int iRecvBytes = recv(iterRecv->sock, iterRecv->szRecvMsg, PACKET_HEADER_SIZE-iterRecv->iTotalRecvBytes, 0);
			if (iRecvBytes == 0)
			{
				printf("클라이언트 접속 종료 : IP:%s, PORT:%d\n", inet_ntoa(iterRecv->address.sin_addr), htons(iterRecv->address.sin_port));
				closesocket(iterRecv->sock);
				iterRecv = userlist.erase(iterRecv);
				continue;
			}
			DWORD dwError = WSAGetLastError();
			if (iRecvBytes == SOCKET_ERROR)
			{
				if (dwError != WSAEWOULDBLOCK)
				{
					closesocket(iterRecv->sock);
					iterRecv = userlist.erase(iterRecv);
				}
				else
				{
					iterRecv++;
				}
				continue;
			}
			UPACKET packet;
			ZeroMemory(&packet, sizeof(packet));

			iterRecv->iTotalRecvBytes += iRecvBytes;

			if (iterRecv->iTotalRecvBytes == PACKET_HEADER_SIZE)
			{
				memcpy(&packet.ph, iterRecv->szRecvMsg, PACKET_HEADER_SIZE);

				char* msg = (char*)&packet;
				int iNumRecvByte = 0;
				do {

					int iRecvBytes = recv(iterRecv->sock, &packet.msg[iNumRecvByte], packet.ph.len - PACKET_HEADER_SIZE - iNumRecvByte, 0);
					if (iRecvBytes == 0)
					{
						printf("정상 종료\n");
						break;
					}
					if (iRecvBytes == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							closesocket(iterRecv->sock);
							printf("비정상 종료");
							return 1;
						}
						continue;
					}
					iNumRecvByte += iRecvBytes;
				} while ((packet.ph.len - PACKET_HEADER_SIZE > iNumRecvByte));
			}

			if (iRecvBytes > 0)
			{
				switch (packet.ph.type)
				{
				case PACKET_CHAR_MSG:
				{
					printf("[%s]%s\n", iterRecv->m_szName, packet.msg);
					packet.ph.len += strlen(iterRecv->m_szName) + 2;
					string pMsg = "[";
					pMsg += iterRecv->m_szName;
					ZeroMemory(packet.msg, 2048);
					memcpy(packet.msg, pMsg.c_str(), pMsg.size());

				}break;
				case PACKET_NAME_REQ:
				{
					memcpy(iterRecv->m_szName, packet.msg, strlen(packet.msg));
					packet.ph.type = PACKET_JOIN_USER;
					SendMsg(iterRecv->sock, nullptr, PACKET_NAME_ACK);
				}break;
				}
				
				for (auto iterSend = userlist.begin();userlist.end() != iterSend;)
				{
					if(packet.ph.type == PACKET_JOIN_USER)
					{
						if ( iterRecv == iterSend)
						{
							iterSend++;
							continue;
						}
					}
					int iSendBytes = send(iterSend->sock, (char*)&packet, packet.ph.len, 0);

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
				ZeroMemory(&packet, sizeof(UPACKET));
				iterRecv->iTotalRecvBytes=0;
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

		SendMsg(clientSock, nullptr, PACKET_CHATNAME_REQ);
		
	}
	closesocket(sock);

	WSACleanup();

	return 0;
}
