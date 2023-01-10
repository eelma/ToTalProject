#pragma once
#include <winsock2.h>
#include <windows.h>
#include <tchar.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <codecvt>
#include <atlconv.h> 
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include"KVector.h"
#include"TMath.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "ws2_32.lib")
#define KCORE
extern float g_fGameTimer;
extern float g_fSecondPerFrame;

using namespace Microsoft::WRL;
using namespace std;

extern HWND g_hWnd;
extern RECT g_rtClient;
extern float g_fGameTimer;
extern float g_fSecondPerFrame;
//extern은 초기화 하면 안된다

typedef basic_string<TCHAR> T_STR;
typedef basic_string<wchar_t> W_STR;
typedef basic_string<char>  C_STR;
typedef vector<basic_string<TCHAR>>		TCHAR_STRING_VECTOR;
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





// 멀티바이트 문자집합 사용경우
	// ABC홍길동 = 9
	// [A][B][C] [0]
	// 유니코드바이트 문자집합 사용경우
	// ABC홍길동 = 12
	// [A][0][B][0][C][0] [][][][][][]
//static wstring mtw(string str)
//{
//	wstring ret = wstring(str.begin(), str.end());
//	return  ret;
//}
//static string wtm(wstring str)
//{
//	return  string(str.begin(), str.end());
//}

//#include <atlconv.h> // A2W
static wstring to_mw(const string& _src)
{
	USES_CONVERSION;
	return wstring(A2W(_src.c_str()));
};

static string to_wm(const wstring& _src)
{
	USES_CONVERSION;
	return string(W2A(_src.c_str()));
};
static wstring mtw(string str)
{
	wstring_convert<codecvt_utf8_utf16<wchar_t>> conv;
	return conv.from_bytes(str);
}
//#include <codecvt>
static string wtm(wstring str)
{
	wstring_convert<codecvt_utf8_utf16<wchar_t>> conv;
	return conv.to_bytes(str);
}
static char* GetWtM(WCHAR* data)
{
	char retData[4096] = { 0 };
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		data, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		data, -1,  //  소스
		retData, iLength, // 대상
		NULL, NULL);
	return retData;
}
static bool GetWtM(WCHAR* src, char* pDest)
{
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		src, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		src, -1,  //  소스
		pDest, iLength, // 대상
		NULL, NULL);
	if (iRet == 0) return false;
	return true;
}
static WCHAR* GetMtW(char* data)
{
	WCHAR retData[4096] = { 0 };
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = MultiByteToWideChar(CP_ACP, 0, data, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		data, -1,  //  소스
		retData, iLength); // 대상
	return retData;
}
static bool GetMtW(char* pSrc, WCHAR* pDest)
{
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1,  //  소스
		pDest, iLength); // 대상		
	if (iRet == 0) return false;
	return true;
}
static void PRINT(char* fmt, ...) // 나열연산자
{
	va_list arg;
	va_start(arg, fmt);
	char buf[256] = { 0, };
	vsprintf_s(buf, fmt, arg);
	printf("\n=====> %s", buf);
	va_end(arg);
}