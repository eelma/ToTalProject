#pragma once
#include "KScene.h"
class KSceneTitle : public KScene
{
public:
	KUser2D* m_pUser;
	KBaseObject* m_pBG;
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual bool        IsNextScene();
};

