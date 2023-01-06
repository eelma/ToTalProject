//파일디스크립터:네트워크 소켓과 같은 파일이나 기타 입력/출력 리소스에 액세스하는 데 사용되는 추상표현이다. 즉, 시스템으로 부터 할당받은 파일이나 소켓을 대표하는 정수다.
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#define SERVER_CODE
#ifndef SERVER_CODE


int main()
{
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		return 0;
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
		printf("%d ", iError);
		return 1;
	}

	u_long iMode = TRUE;
	ioctlsocket(sock, FIONBIO, &iMode);//논블락
	
	while (1)
	{
		Sleep(100);
		char szSendMsg[256] = {0,};
		printf("%s", "send---->");
		fgets(szSendMsg, 256, stdin);

		int iSendBytes = send(sock, szSendMsg, sizeof(szSendMsg), 0);
		if (iSendBytes == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(sock);
				return 1;
			}
			continue;
		}

		char szRecvMsg[256] = { 0, };
		int iRecvBytes = recv(sock, szRecvMsg, sizeof(szRecvMsg), 0);
		if(iRecvBytes == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(sock);
				return 1;
			}
			continue;
		}
		printf("Recv_____%s\n", szRecvMsg);
	}
	closesocket(sock);
	WSACleanup();

}


#else

int main()
{
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY는 자동으로 이 컴퓨터에 존재하는 랜카드 중 사용가능한 랜카드의 IP주소를 사용하라는 의미
	sa.sin_port = htons(10000);
	int iRet = bind(sock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return 1;
	}
	iRet = listen(sock, SOMAXCONN);//연결 요청 소켈이 대기하는 연결 대기열을 생성한다 윈속2부터는 somaxcoon 상수를 사용하는데 소켓 서비스 제공자가 알아서 backlog값을 설정한다.
	if(iRet == SOCKET_ERROR)
	{
		return 1;
	}
	//접속되면 반환된다
	SOCKADDR_IN clientaddr;
	int length = sizeof(clientaddr);
	SOCKET clientSock = accept(sock, (sockaddr*)&clientaddr, &length);//클라이언트 접속을 수용할 목적으로 만든 소켓, 소켓 주소 구조체, 소켓 주소 구조체 변수의 길이(바이트 단위)
	//성공시 0을 반환, 실패시 -1orSOCKET_ERROR을 반환
	if (clientSock == SOCKET_ERROR)
	{
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	printf("클라이언트 접속 IP:%s, PORT: %d", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	u_long iMode = TRUE;
	ioctlsocket(clientSock, FIONBIO, &iMode);//논블로킹 소켓으로 만드는 소켓
											 //논블로킹모드로 설정할 소켓, 소켓에대해 수행할 동작을 의미, cmd가 수행할 동작에 대한 판별값 0이면 블로킹모드 0이 아니면 논블로킹모드

	while (1)
	{
		char szRecvMsg[256] = { 0, };
		int iRecvBytes = recv(clientSock, szRecvMsg, 256, 0);//connect, accept로 연결된 소켓디스크립터, data를 수신하여 저장할 버퍼, 읽을 데이터 크기, 읽을 데이터 유형or옵션
		if (iRecvBytes == 0)
		{
			printf("클라이언트 접속 종료 : IP:%s, PORT:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			closesocket(clientSock);
			break;
		}
		if (iRecvBytes == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)//WSAGetLastError은 마지막 오류를 반환
				/*넌블록 소켓에서 WSAEWOULDBLOCK의 의미
				WSAAcceptm, accept = 연결 요청 받지 못함
				closesocket = SO_LINGER옵션에 타임아웃
				WSAConnect, connect = 연결 시도
				recv함수들 = 데이터 아직 못받음 : 다시 요청해야함
				send 함수들 = 전송할 버퍼 공간 없음, 나중에 다시 시도
				*/
			{
				//WSAEWOULDBLOCK 아니라면 오류
				closesocket(sock);
				return 1;
			}
		}
		else
		{
			printf("%s \n", szRecvMsg);
		}
		if (iRecvBytes > 0)
		{
			int iSendBytes = send(clientSock, szRecvMsg, sizeof(szRecvMsg),0);
			if(iSendBytes == SOCKET_ERROR)
			{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(clientSock);
				break;
			}
			}
		}

	}
	closesocket(clientSock);
	WSACleanup();
	std::cout << "Hello\n";
}


#endif // !SERVER_CODE