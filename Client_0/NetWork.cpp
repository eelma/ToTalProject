#include "NetWork.h"
DWORD WINAPI RecvThread(LPVOID IpThreadParameter)
{

	NetWork* net = (NetWork*)IpThreadParameter;
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
		return true;
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
			int iRecvBytes = recv(net->m_Sock, &packet.msg[iNumRecvByte], packet.ph.len - PACKET_HEADER_SIZE - iNumRecvByte, 0);

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
					printf("서버 비정상 종료\n");
					return 1;
				}
				continue;
			}
			iNumRecvByte += iRecvBytes;

		} while ((packet.ph.len - PACKET_HEADER_SIZE) > iNumRecvByte);

		net->m_PacketList.push_back(packet);
		iTotalRecvBytes = 0;
	}
	}
	closesocket(sock);
};
int NetWork::SendMsg(SOCKET sock, const char* msg, short type)
{


	return 0;
}