#pragma once
#include"KVector.h"
struct float3x3
{
	union
	{

		struct {
			float _11, _12, _13;
			float _21, _22,_23;
			float _31, _32, _33;
		};
		float m[3][3];
	};
};
struct float4x4
{

	union
	{
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31,_32,_33,_34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};

};
class KMatrix3x3 :public float3x3
{
public:
	KMatrix3x3();
	void Identity();
	KMatrix3x3 Transpose();
	KMatrix3x3 Rotation(float fRadian);
	KMatrix3x3 Scale(float x, float y);
	KMatrix3x3 Translation(float x, float y);
public:
	KMatrix3x3 operator*(KMatrix3x3& m);
};

class KMatrix: public float4x4
{
public:
	KMatrix();
	void Identity();
	KMatrix Transpose();
	KMatrix RotationX(float fRadian);
	KMatrix RotationY(float fRadian);
	KMatrix RotationZ(float fRadian);
	KMatrix Scale(float x, float y,float z);
	KMatrix Translation(float x, float y, float z);

	

public:
	KMatrix operator* (KMatrix& m);

};

