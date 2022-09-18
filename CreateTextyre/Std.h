#pragma once
#include<Windows.h>
#include<iostream>
#include<map>
#include<vector>
#include<list>
#include<set>
#include<string>
#include<d3d11.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

extern HWND g_hWnd;
extern RECT g_rtClient;

using namespace std;


#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR  lpCmdLine, int  nCmdShow){
#define GAME_WINDOW(s,x,y) Sample demo; demo.SetWindow(hInstance,L#s,x,y);demo.Run();return 1;
#define GAME_END }
#define GAME_RUN(s,x,y) GAME_START GAME_WINDOW(s,x,y) GAME_END
//반드시 실행하려면 sample 클래스의 인스턴스가 있어야한다