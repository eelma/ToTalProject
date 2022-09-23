#pragma once
#include "KGameCore.h"
#include"KUser2D.h"
#include"KNpc2D.h"

class Sample : public KGameCore
{
	KBaseObject*			m_pMap;
	vector<KBaseObject*>	m_pNpcList;
	KUser2D*				m_pUser;
	vector<KBaseObject*>	m_pObjectList;

public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
};

