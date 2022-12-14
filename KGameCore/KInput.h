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
	DWORD m_dwKeyState[256];//mouse 포함 모든 버튼 
public:
	POINT m_ptPos;//mouse position
	POINT m_ptPrePos;
	POINT m_ptOffset;
public:
	virtual bool		Init(); // 초기화
	virtual bool		Frame();// 실시간 계산
	virtual bool		Render();// 실시간 랜더링
	virtual bool		Release();// 소멸 및 삭제

public:
	DWORD GetKey(DWORD dwkey);

};

#define I_Input KInput::GetInstance()