#pragma once
#include<list>
using namespace std;
#define PACKET_HEADER_SIZE 4
#pragma pack(push,1)
typedef struct
{
	short len;
	short type;
}PACKET_HEADER;
typedef struct
{
	PACKET_HEADER ph;//short 2개 (len, type)
	char msg[2048];
}UPACKET;
typedef struct
{

	char szName[9];

}USERNAME_REQ;
typedef struct
{

	int iResult;//1 성공 0 중복 0>실패

}USERNAME_ACK;

#pragma pack(pop)
struct User
{
	SOCKET sock;
	SOCKADDR_IN address;
	char m_szName[9] = { 0, };
	char szRecvMsg[256] = {0,};
	int iTotalRecvBytes = 0;
};
list<User>userlist;
#define PACKET_CHAR_MSG 1000 // client ->
#define PACKET_CHATNAME_REQ 1001 // server -> client
#define PACKET_NAME_REQ 2000 // client -> server
#define PACKET_NAME_ACK 3000 // server -> client
#define PACKET_JOIN_USER 4000 // server -> client