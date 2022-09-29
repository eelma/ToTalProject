#pragma once
#include"KScene.h"
class KSceneTitle:public KScene
{

public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();

};

