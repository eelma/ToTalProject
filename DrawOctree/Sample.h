#pragma once
#include "KDevice.h"
#include"KBaseObject.h"
#include "KGameCore.cpp"
class Sample : public KDevice
{
	KGameCore<KObject2D>game2D;
	KGameCore<KObject>game3D;

	KBaseObject m_object;

public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
};

