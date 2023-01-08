#pragma once
#include<list>
using namespace std;
struct User
{
	SOCKET sock;
	SOCKADDR_IN address;
};
list<User>userlist;