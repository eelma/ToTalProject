#pragma once
#include"KDevice.h"

class KGameCore:public KDevice
{
public:
	bool bGameRun = true;
public:
	virtual bool		Init() { return true; }; // �ʱ�ȭ
	virtual bool		Frame() { return true; };// �ǽð� ���
	virtual bool		Render() { return true; };// �ǽð� ������
	virtual bool		Release() { return true; };// �Ҹ� �� ����

	//������Ʈ���� �ǵ��� ����� �����̺����� ����� ��������
private:
	bool		KCoreInit(); // �ʱ�ȭ
	bool		KCoreFrame();// �ǽð� ���
	bool		KCoreRender();// �ǽð� ������
	bool		KCorePreRender();
	bool		KCorePostRender();
	bool		KCoreRelease();// �Ҹ� �� ����	
public:
	bool		Run()override; // �Ҹ� �� ����	

};

