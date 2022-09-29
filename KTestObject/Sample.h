#pragma once
#include "KGameCore.h"
#include "KSceneTitle.h"
#include "KSceneInGame.h"
class Sample : public KGameCore
{
public:
	KSceneTitle* m_pTitle = nullptr;
	KSceneInGame* m_pInGame = nullptr;
	KScene* m_pCurrentScene = nullptr;
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};

