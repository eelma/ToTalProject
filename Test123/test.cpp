#include<iostream>
using namespace std;

int main()
{
	
	char i[5] = { 1,2,3,4,5 };
	char b[100] = {0,};
	memcpy(b, &i, 3);
}