#pragma once
#include "KDevice.h"
#include"KBaseObject.h"
class Sample : public KDevice
{
	vector<KBaseObject*> m_pObjectList;
	int m_iTexIndex;

public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
};

