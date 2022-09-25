#pragma once
#include"KGameCore.h"
#include"KWriter.h"

class Sample : public KGameCore
{
	KWriter m_Writer;

public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
	//virtual bool Run()override;

};

