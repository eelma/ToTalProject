#pragma once
#include"KStd.h"
class KTimer
{
public:
	float m_fGameTimer = 0.0f;
	float m_fElapseTimer = 10;
	UINT m_iFPS = 0;
public:
	DWORD dwBeforeTime;
	UINT fps = 0;
	UINT counter = 0;
	float fFps = 0.0f;

public:
	virtual bool		Init(); // �ʱ�ȭ
	virtual bool		Frame();// �ǽð� ���
	virtual bool		Render();// �ǽð� ������
	virtual bool		Release();// �Ҹ� �� ����
};

