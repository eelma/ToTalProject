#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
//#define SERVER_CODE
#ifndef SERVER_CODE


int main()
{

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		return 0;
	}
	SOCKET sock3 = socket(AF_INET, SOCK_STREAM, 0);
	//client

	SOCKADDR_IN sa;//목적지+포트

	sa.sin_family = AF_INET;

	sa.sin_addr.s_addr = inet_addr("192.168.0.86");

	sa.sin_port = htons(10000);
	int iRet = connect(sock3, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) { return 1; }
	char szSendMsg[256] = { 0, };
	fgets(szSendMsg, 256, stdin);
	int iSendBytes = send(sock3, szSendMsg, strlen(szSendMsg), 0);
	char szRecvMsg[256] = { 0, };
	int iRecvBytes = recv(sock3, szSendMsg, 256, 0);
	printf("%s\n", szRecvMsg);
	closesocket(sock3);
	WSACleanup();
	std::cout << "wtf";
}


#else

int main()
{
	//윈속 초기화 정보 구조체
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		//첫번째 인수는 윈속의 버전을 지정한다 makeword는 2개의 인수를 word로 pack 하는 매크로다
		//word는 16비트의 부호가 없는 변수로 wsastartup()에서는 word의 16비트에서 상위 8비트에 major번호 하위 8비트에 minor번호를 넣어 넘겨주어야한다.
		//wsastartup의 두번째 인수는 wsastartup이 초기화된 상태를 저장하는 변수를 넘겨준다.
		//wsatartup()은 윈속을 초기화하고 초기화한 상태를 wsadata구조체에 저장한다
	{
		return 0;
	}
	//SOCKET sock1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//SOCKET sock2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKET sock3 = socket(AF_INET, SOCK_STREAM, 0);//TCP, 스트림 소켓,(0=인터넷 프로토콜) 주소체계, 소켓타입, 사용할 프로토콜
	//반환값: SOCKET(32비트 정수) 성공시 새로운 소켓, 실패시 INVAILID_SOCKET
	short sData = 10000;
	short tData = 0x271094;
	short fData = 0x1027;
	

	short test1 = htons(0x12345678);
	short test2 = ntohs(0x12345678);
	
	//client
	SOCKADDR_IN sa;//목적지+포트
	sa.sin_family = AF_INET;//socket에서 주소체계를 저장하는 변수이다 TCP/IP프로토콜을 사용하면 값은 AF_INET가 된다
	sa.sin_addr.s_addr = htonl(INADDR_ANY);//ip주소를 나타내며 32비트 in_addr 구조체를 사용한다 INADDR_ANY는 자동으로 이 컴퓨터에 존재하는 랜카드 중 사용가능한 랜카드의 IP주소를 사용하라는 의미
	sa.sin_port = htons(10000); //포트번호를 나타내며 부호없는 16비트 정수값을 사용한다.

	//htons와 htonl은 바이트 정렬으로 네트워크에선 무조건 빅엔디안(최상위 바이트부터 차례로 저장되는 방식)을 사용한다 리틀엔디안은 거꾸로 저장해서 절대 쓰면 안된다
	//htonl long intger(일반적으로 4byte)데이터를 네트워크 byte order로 변경한다. 호스트 바이트 -> 네트워크 바이트
	//htons short intger(일반적으로 2byte)데이터를 네트워크 byte order로 변경한다. 호스트 바이트 -> 네트워크 바이트

	int iRet = bind(sock3, (sockaddr*)&sa, sizeof(sa));//로컬 주소를 소켓과 연결한다 socket, const sockaddr*name, namelen 
	if (iRet == SOCKET_ERROR)
	{
		return 1;
	}
	iRet = listen(sock3, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
	{
		return 1;
	}
	//접속되면 반환된다.
	SOCKADDR_IN clientaddr;
	int length = sizeof(clientaddr);
	SOCKET clientSock = accept(sock3, (sockaddr*)&clientaddr, &length);//클라이언트 접속을 수용할 목적으로 만든 소켓, 소켓 주소 구조체, 소켓 주소 구조체 변수의 길이(바이트 단위)
	//성공시 0을 반환, 실패시 -1orSOCKET_ERROR을 반환
	printf("클라이언트 접속: IP%s, PORT:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));//inet_ntoa는 네트워크 바이트 순서의 32비트 값을 dotted decimal notation의 주소값으로 변환한다
	// inet_addr <-> inet_ntoa

	char szRecvMsg[256] = { 0, };
	int iRecvBytes = recv(clientSock, szRecvMsg, 256, 0);
	printf("%s\n", szRecvMsg);

	int iSendBytes = send(clientSock, szRecvMsg, strlen(szRecvMsg), 0);

	closesocket(sock3);

	WSACleanup();
	std::cout << "HelloWorld!\n";


}


#endif // !SERVER_CODE