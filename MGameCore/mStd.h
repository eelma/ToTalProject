#pragma once
#include<Windows.h>
#include <windows.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <d3d11.h>
#include <codecvt>
#include <d3dcompiler.h>
#include<crtdbg.h>
#include<cstdlib>
#include <wrl.h>
using namespace std;
using namespace Microsoft::WRL;
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
#define mCore
extern HWND g_hWnd;
extern RECT g_rtClient;

typedef basic_string<TCHAR> T_STR;
typedef basic_string<wchar_t> W_STR;
typedef basic_string<char>  C_STR;
typedef vector<std::basic_string<TCHAR>>		TCHAR_STRING_VECTOR;
typedef vector<DWORD>					DWORD_VECTOR;

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