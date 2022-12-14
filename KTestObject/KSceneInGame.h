#pragma once
#include "KScene.h"
class KSceneInGame : public KScene
{
public:
	KMapObject* m_pMap;
	vector<KNpc2D*>		m_pNpcList;
	vector<KTexture*>		m_ObjectTextureList;
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual void DrawMiniMap(UINT x, UINT y, UINT w = 100, UINT h = 100);
};

