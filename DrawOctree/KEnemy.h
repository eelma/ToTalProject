#pragma once
#include "KObject.h"
class KEnemy : public KObject
{
public:
	bool   Frame(float fDeltaTime, float fGameTime) override;
	bool   Render() override;
	KEnemy();
	KEnemy(std::string name);
};
class KEnemy2D : public KObject2D
{
public:
	bool   Frame(float fDeltaTime, float fGameTime) override;
	bool   Render() override;
	KEnemy2D();
	KEnemy2D(std::string name);
};

