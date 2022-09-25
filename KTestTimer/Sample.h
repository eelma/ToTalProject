#pragma once
#include"KGameCore.h"
#include"KTimer.h"

class Sample : public KGameCore
{

public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
	//virtual bool Run()override;

};

