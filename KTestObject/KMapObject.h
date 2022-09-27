#pragma once
#include"KBaseObject.h"
#include"KInput.h"
class KMapObject: public KBaseObject
{
public:
	KVector2D m_vUser;
public:
	bool Frame();
	bool Render();

};

