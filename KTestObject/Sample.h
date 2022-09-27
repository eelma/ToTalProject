#pragma once
#include "KGameCore.h"
#include "KBaseObject.h"
#include "KTextureManager.h"
#include "KShaderManager.h"
#include"KMapObject.h"
#include"KUser2D.h"

class Sample : public KGameCore
{
public:
	KUser2D* m_pUser;
	KMapObject* m_pMap;
public:
	std::vector<KBaseObject*>	m_ObjectList;
	std::vector<KTexture*>		m_ObjectTextureList;
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};

