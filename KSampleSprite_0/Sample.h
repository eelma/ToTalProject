#pragma once
#include "KGameCore.h"
#include"KBaseObject.h"

class KUser2D :public KBaseObject
{
public:
	KTexture* m_pTexture;
	POINT m_pkImageSize;
	RECT m_rt;//�̹����� ���� ũ��
	KRect m_rtInit;
	KRect m_rtUV;
	KVector2D m_vPos;
	KVector2D m_vSize;

public:
	void SetPosition(KVector2D vPos);
	void SetRect(KRect rt);
	void UpdateVertexBuffer();



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

