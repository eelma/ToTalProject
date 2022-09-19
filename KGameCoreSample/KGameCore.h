#pragma once
#include"KDevice.h"
#include"KTimer.h"
class KGameCore:public KDevice
{
public:
	KTimer m_Timer;
	bool m_bGameRun = true;
public:
	virtual bool		Init() { return true; }; // �ʱ�ȭ
	virtual bool		Frame() { return true; };// �ǽð� ���
	virtual bool		Render() { return true; };// �ǽð� ������
	virtual bool		Release() { return true; };// �Ҹ� �� ����

private:
	bool		KCoreInit(); // �ʱ�ȭ
	bool		KCoreFrame();// �ǽð� ���
	bool		KCoreRender();// �ǽð� ������
	bool		KCorePreRender();
	bool		KCorePostRender();
	bool		KCoreRelease();// �Ҹ� �� ����	
public:
	bool		Run();// �Ҹ� �� ����	

};

