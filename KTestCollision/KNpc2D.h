#pragma once
#include "KObject2D.h"
class KNpc2D : public KObject2D
{
public:
	bool  Frame() override;
	KNpc2D()
	{
		m_fSpeed = 300.0f;
	}
};

