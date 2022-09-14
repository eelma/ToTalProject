#pragma once
#include "KDevice.h"
#include"KBaseObject.h"
#include "KGameCore.cpp"
class Sample : public KDevice
{
	KGameCore<KObject2D>game2D;
	KGameCore<KObject>game3D;

	KBaseObject m_object;

public:
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제
};

