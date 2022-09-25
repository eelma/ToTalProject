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