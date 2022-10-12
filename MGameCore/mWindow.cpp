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
	//����� ��忡�� ������ ����� ġ�����ϰ��̶�� ���� �ɾ���� ���� ����� �ڵ�
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
		PostQuitMessage(0);//�޼���ť�� ���� WM_QUIT
		break;
	}
	return DefWindowProc(hWnd, message, wParam, IParam);
}