#pragma once
#include <windows.h>
#include <iostream>
#include <math.h>
#define T_PI 3.141592f
#define DegreeToRadian(x)  (x *(T_PI / 180.0f))
#define RadianToDegree(x) (x *(180.0f / T_PI))
#define T_Epsilon 0.001f
class KMatrix;
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
class KVector4 : public KFloat4
{
public:
	KVector4();
	KVector4(float x, float y, float z, float w);
	KVector4(const KVector4& v);
public:
	KVector4 operator + (KVector4& v);
	KVector4 operator - (KVector4& v);
	KVector4 operator * (float scala);
	KVector4 operator / (float scala);
	KVector4 operator *= (float scala);
	KVector4 operator += (KVector4& v);
	KVector4 operator -= (KVector4& v);
	bool      operator == (KVector4& v);
	bool      operator <= (KVector4& v);
	bool      operator >= (KVector4& v);
public:
	float     LengthSquared();
	float     Length();
	void      Normalized();
	KVector4 Identity();
	float     Angle(KVector4& v);
};

class KVector2 : public KFloat2
{
public:
	KVector2();
	KVector2(float x, float y);
	KVector2(const KVector2& v);
public:
	KVector2 operator + (KVector2& v);
	KVector2 operator - (KVector2& v);
	KVector2 operator * (float scala);
	KVector2 operator / (float scala);
	KVector2 operator *= (float scala);
	KVector2 operator += (KVector2& v);
	KVector2 operator -= (KVector2& v);
	bool      operator == (KVector2& v);
	bool      operator <= (KVector2& v);
	bool      operator >= (KVector2& v);
public:
	float     LengthSquared();
	float     Length();
	void      Normalized();
	KVector2 Identity();
	float     Angle(KVector2& v);
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

	KVector  operator* (KMatrix& m);



	KVector Normal();


};

