#pragma once
#include "KScene.h"
#include"KShape.h"
#include"KCamera.h"
#include"KMap.h"
#include"KObject3D.h"
#include"KCameraDebug.h"
class KSceneTitle : public KScene
{
public:
	KUser2D* m_pUser;
	KBaseObject* m_pBG;
	KObject3D* m_pBoxObj = nullptr;

	KMap* m_pMap = nullptr;

public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual bool        IsNextScene();
};

