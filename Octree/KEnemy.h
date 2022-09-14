#pragma once
#include "KObject.h"
class KEnemy : public KObject
{
public:
	void   Frame(float fDeltaTime, float fGameTime) override;
	void   Render() override;
	KEnemy();
	KEnemy(std::string name);
};
class KEnemy2D : public KObject2D
{
public:
	void   Frame(float fDeltaTime, float fGameTime) override;
	void   Render() override;
	KEnemy2D();
	KEnemy2D(std::string name);
};

