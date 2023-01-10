#include "Sample.h"
bool Sample::Init()
{
	return true;
}
bool Sample::Frame()
{
	return true;
}
bool Sample::Render()
{
	return true;
}
bool Sample::Release()
{
	return true;
}
void Sample::Print(const WCHAR* msg, ...)
{



}
LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{



}
bool Sample::Run()
{
	Init();
	while (bGameRun)
	{
		if (KWindow::Run() == true)
		{
			Frame();
			Render();
		}


	}

}