#pragma once
#include "KObject2D.h"
class KMapObject : public KObject2D
{
	bool   FrameScroll();
public:
	bool   Frame() override;
	void  UpdateVertexBuffer() override;
};

