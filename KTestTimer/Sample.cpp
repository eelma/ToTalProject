#include "Sample.h"
bool Sample::Init()
{
	I_Timer.Init();
	
	return true;
}

bool Sample::Frame()
{
	I_Timer.Frame();
	return true;
}

bool Sample::Render()
{ 
	I_Timer.Render();
	
	return true;
}

bool Sample::Release()
{
	I_Timer.Release();
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