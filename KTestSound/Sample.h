#pragma once
#include "KGameCore.h"
#include "KSound.h"

class Sample : public KGameCore
{
	KSound				m_Sound;
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};

