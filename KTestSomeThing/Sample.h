#pragma once
#include "KGameCore.h"
#include "KSceneTitle.h"
#include "KSceneInGame.h"
class Sample : public KGameCore
{
public:
	shared_ptr<KSceneTitle> m_pTitle = nullptr;
	shared_ptr < KSceneInGame> m_pInGame = nullptr;
	shared_ptr < KScene> m_pCurrentScene = nullptr;
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};

