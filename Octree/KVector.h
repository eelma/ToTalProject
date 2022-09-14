#pragma once
#include <windows.h>
#include <iostream>
#include <math.h>
#define T_PI 3.141592f
#define DegreeToRadian(x)  (x *(T_PI / 180.0f))
#define RadianToDegree(x) (x *(180.0f / T_PI))
#define T_Epsilon 0.001f
struct TFloat2
{
	union
	{
		struct {
			float x;
			float y;
		};
		float v[2];
	};
};
struct TFloat3
{
	union
	{
		struct {
			float x;
			float y;
			float z;
		};
		float v[3];
	};
};
class KVector2D : public TFloat2
{
public:
	KVector2D();
	KVector2D(float x, float y);
	KVector2D(const KVector2D& v);
public:
	KVector2D operator + (KVector2D& v);
	KVector2D operator - (KVector2D& v);
	KVector2D operator * (float scala);
	KVector2D operator / (float scala);
	KVector2D operator *= (float scala);
	KVector2D operator += (KVector2D& v);
	KVector2D operator -= (KVector2D& v);
	bool      operator == (KVector2D& v);
	bool      operator <= (KVector2D& v);
	bool      operator >= (KVector2D& v);
public:
	float     LengthSquared();
	float     Length();
	void      Normalized();
	KVector2D Identity();
	float     Angle(KVector2D& v);
};

class KVector : public TFloat3
{
public:
	KVector();
	KVector(float x, float y, float z);
	KVector(const KVector& v);
public:
	KVector operator + (KVector& v);
	KVector operator - (KVector& v);
	KVector operator * (float scala);
	KVector operator / (float scala);
	KVector operator *= (float scala);
	KVector operator += (KVector& v);
	KVector operator -= (KVector& v);
	bool      operator == (KVector& v);
	bool      operator <= (KVector& v);
	bool      operator >= (KVector& v);
public:
	float     LengthSquared();
	float     Length();
	void      Normalized();
	KVector Identity();
	float     Angle(KVector& v);
};

