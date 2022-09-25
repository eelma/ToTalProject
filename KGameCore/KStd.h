#pragma once
#include <windows.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include"KVector.h"

#define KCORE
using namespace std;

extern HWND g_hWnd;
extern RECT g_rtClient;

//extern�� �ʱ�ȭ �ϸ� �ȵȴ�
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