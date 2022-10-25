#pragma once
#include"KStd.h"
enum KeyState
{

	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,


};
class KInput :public KSingleTone<KInput>
{
private:
	DWORD m_dwKeyState[256];//mouse ���� ��� ��ư 
public:
	POINT m_ptPos;//mouse position
	POINT m_ptPrePos;
	POINT m_ptOffset;
public:
	virtual bool		Init(); // �ʱ�ȭ
	virtual bool		Frame();// �ǽð� ���
	virtual bool		Render();// �ǽð� ������
	virtual bool		Release();// �Ҹ� �� ����

public:
	DWORD GetKey(DWORD dwkey);

};

#define I_Input KInput::GetInstance()