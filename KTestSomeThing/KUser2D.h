#pragma once
#include "KObject2D.h"
class KUser2D : public KObject2D
{
public:
	bool  Frame() override;
	KUser2D()
	{
		m_fSpeed = 400.0f;
	}
};

