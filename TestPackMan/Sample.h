#pragma once
#include "KGameCore.h"
#include"KSceneTitle.h"

class Sample : public KGameCore
{
public:
	KSceneTitle* m_pTitle = nullptr;
	KScene* m_pInGame = nullptr;
	KScene* m_pCurrentScene = nullptr;

	KSound* m_pBGSound = nullptr;
	KSound* m_pShot = nullptr;
	KSound* m_pEffect = nullptr;
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};

