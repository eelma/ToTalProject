#pragma once
#include "KDevice.h"
#include"KBaseObject.h"
class Sample : public KDevice
{
	vector<KBaseObject*> m_pObjectList;

public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
};

