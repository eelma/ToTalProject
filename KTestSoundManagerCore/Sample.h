#pragma once
#include "KGameCore.h"

class Sample : public KGameCore
{
	KSound* m_pBGSound = nullptr;
	KSound* m_pShot = nullptr;
	KSound* m_pEffect = nullptr;
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};

