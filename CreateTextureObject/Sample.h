#pragma once
#include "KDevice.h"
#include"KBaseObject.h"
class Sample : public KDevice
{
	KBaseObject m_object;

public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
};

