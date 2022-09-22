#pragma once
#include "KGameCore.h"
#include"KBaseObject.h"

class KUser2D :public KBaseObject
{
public:
	KTexture* m_pMaskTex = nullptr;
	POINT m_pkImageSize;
	RECT m_rt;//�̹����� ���� ũ��
	KRect m_rtInit;
	KRect m_rtUV;
	//��ũ���� ������
	KVector2D m_vPos;
//	KVector2D m_vSize;
private:
	KVector2D m_vDrawPos;
	KVector2D m_vDrawSize;

public:
	bool Frame()override;
	void SetPosition(KVector2D vPos);
	void SetRect(KRect rt);
	void UpdateVertexBuffer();
	void SetMask(KTexture* pMaskTex)
	{
		m_pMaskTex = pMaskTex;
	}

};
class KNpc2D :public KBaseObject
{
public:
	POINT m_pkImageSize;
	RECT m_rt;//�̹����� ���� ũ��
	KRect m_rtInit;
	KRect m_rtUV;
	//��ũ���� ������
	KVector2D m_vPos;
	//	KVector2D m_vSize;
private:
	KVector2D m_vDrawPos;
	KVector2D m_vDrawSize;

public:
	bool Frame()override;
	void SetPosition(KVector2D vPos);
	void SetRect(KRect rt);
	void UpdateVertexBuffer();
	



};
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

