#pragma once
#include"KDevice.h"


class Sample : public KDevice
{

public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
	virtual bool Run()override;

};

