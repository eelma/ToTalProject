#pragma once
#include "KScene.h"
#include"KShape.h"
#include"KCamera.h"
class KSceneTitle : public KScene
{
public:
	KUser2D* m_pUser;
	KBaseObject* m_pBG;
	KShapeBox* m_pBoxObj = nullptr;
	KCamera* m_pMainCamera = nullptr;

public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual bool        IsNextScene();
};

