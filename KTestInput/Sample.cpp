#include "Sample.h"
bool Sample::Init()
{
	I_Input.Init();
	
	return true;
}

bool Sample::Frame()
{
	I_Input.Frame();
	if (I_Input.GetKey('W') != KEY_FREE)
	{
		INT k = 0;
	}
	if (I_Input.GetKey('A') != KEY_FREE)
	{
		INT k = 0;
	}
	if (I_Input.GetKey('S') != KEY_FREE)
	{
		INT k = 0;
	}
	if (I_Input.GetKey('D') != KEY_FREE)
	{
		INT k = 0;
	}
	return true;
}

bool Sample::Render()
{
	
	I_Input.Render();
	wstring test = to_wstring(I_Input.m_ptPos.x);
	test += L" ";
	test += to_wstring(I_Input.m_ptPos.y);
	test += '\n';
	OutputDebugString(test.c_str());
	return true;
}

bool Sample::Release()
{
	I_Input.Release();
	return true;
}

//bool Sample::Run()
//{
//	Init();
//	bool bGameRun = true;
//	while (bGameRun)
//	{
//		if (KWindow::Run() == true)
//		{
//			Frame();
//			Render();
//			
//		}
//		else
//		{
//			bGameRun = false;
//		}
//		
//	}
//	
//	Release();
//	return true;
//}

GAME_RUN(KGameCoreSample1, 800, 600)