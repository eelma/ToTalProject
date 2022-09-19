#pragma once
#include"KDevice.h"
#include"KTimer.h"
class KGameCore:public KDevice
{
public:
	KTimer m_Timer;
	bool m_bGameRun = true;
public:
	virtual bool		Init() { return true; }; // 초기화
	virtual bool		Frame() { return true; };// 실시간 계산
	virtual bool		Render() { return true; };// 실시간 랜더링
	virtual bool		Release() { return true; };// 소멸 및 삭제

private:
	bool		KCoreInit(); // 초기화
	bool		KCoreFrame();// 실시간 계산
	bool		KCoreRender();// 실시간 랜더링
	bool		KCorePreRender();
	bool		KCorePostRender();
	bool		KCoreRelease();// 소멸 및 삭제	
public:
	bool		Run();// 소멸 및 삭제	

};

