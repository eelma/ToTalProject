#pragma once
#include "KGameCore.h"
#include"KBaseObject.h"
class Sample : public KGameCore
{
	vector<KBaseObject*> m_pObjectList;

public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
};

