#pragma once
#include <windows.h>
#include <iostream>
#include <math.h>
#define T_PI 3.141592f
#define DegreeToRadian(x)  (x *(T_PI / 180.0f))
#define RadianToDegree(x) (x *(180.0f / T_PI))
#define T_Epsilon 0.001f
struct KFloat2
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
struct KFloat3
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
struct KFloat4
{
	union
	{
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};
};
class KVector4D : public KFloat4
{
public:
	KVector4D();
	KVector4D(float x, float y, float z, float w);
	KVector4D(const KVector4D& v);
public:
	KVector4D operator + (KVector4D& v);
	KVector4D operator - (KVector4D& v);
	KVector4D operator * (float scala);
	KVector4D operator / (float scala);
	KVector4D operator *= (float scala);
	KVector4D operator += (KVector4D& v);
	KVector4D operator -= (KVector4D& v);
	bool      operator == (KVector4D& v);
	bool      operator <= (KVector4D& v);
	bool      operator >= (KVector4D& v);
public:
	float     LengthSquared();
	float     Length();
	void      Normalized();
	KVector4D Identity();
	float     Angle(KVector4D& v);
};

class KVector2D : public KFloat2
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

class KVector : public KFloat3
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
	bool    operator == (KVector& v);
	bool    operator <= (KVector& v);
	bool    operator >= (KVector& v);
	float	operator| (KVector const& v0);
	KVector operator ^ (KVector const& v0);


public:
	float     LengthSquared();
	float     Length();
	void      Normalized();
	KVector Identity();
	float     Angle(KVector& v);
};

