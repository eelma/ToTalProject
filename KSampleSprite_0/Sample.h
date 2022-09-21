#pragma once
#include "KGameCore.h"
#include"KBaseObject.h"

class KUser2D :public KBaseObject
{
public:
	KRect m_rt;
	KVector2D m_vPos;
public:
	void SetPosition(KVector2D vPos);
	void SetRect(KRect rt);



};
class Sample : public KGameCore
{
	KUser2D*				 m_pUser;
	vector<KBaseObject*> m_pObjectList;

public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
};

