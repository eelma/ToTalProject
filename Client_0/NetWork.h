#pragma once
#include"KStd.h"
#include"Protocal.h"
class NetWork
{
public:
	SOCKET m_Sock;
	HANDLE m_hClientTread;
	list<UPACKET>m_PacketList;
public:
	bool NetStart(string ip, int iPort);
	int SendMsg(SOCKET sock, const char* msg, short type);
	bool Frame();
	bool Render();
	bool Release();
public:
	NetWork();
	virtual ~NetWork();
};

