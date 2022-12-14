#pragma once
#include <windows.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <d3d11.h>
#include <d3dcompiler.h>
#include<crtdbg.h>
#include<cstdlib>
#include"DDSTextureLoader.h"
#include"WICTextureLoader.h"
#pragma comment(lib, "winmm.lib")//timeGetTime
#pragma comment(lib,"DirectXTK.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
using namespace std;

extern HWND g_hWnd;
extern RECT g_rtClient;

extern float g_fGameTimer;
extern float g_fSecondPerFrame;
//extern은 초기화 하면 안된다
template<class T> 
class KSingleTone
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}
};

#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off)(off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;

#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR    lpCmdLine,int       nCmdShow){
#define GAME_WINDOW(s,x,y) Sample demo;demo.SetWindow(hInstance,L#s,x,y);demo.Run();return 1;
#define GAME_END    }
#define GAME_RUN(s,x,y)  GAME_START  GAME_WINDOW(s,x,y)  GAME_END