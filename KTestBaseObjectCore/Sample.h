#pragma once
#include"KGameCore.h"
#include"KObjectPlane.h"

class Sample : public KGameCore
{
	KObjectPlane m_Plane;
public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
	

};

