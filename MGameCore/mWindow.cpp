#include "mWindow.h"

HWND g_hWnd;
RECT g_rtClient;
mWindow* g_pWindow = nullptr;
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM IParam
)
{
	//디버깅 모드에서 오류가 생기면 치명적일것이라는 곳에 심어놓는 에러 검출용 코드
	_ASSERT(g_pWindow);
	return g_pWindow->MsgProc(hWnd, message, wParam, IParam);
}

LRESULT mWindow::MsgProc(
		HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM IParam)
{

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//메세ㅈ큐에 직접 WM_QUIT
		break;
	}
	return DefWindowProc(hWnd, message, wParam, IParam);
}