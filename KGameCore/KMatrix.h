#pragma once
#include"TMath.h"
#include"KVector.h"
namespace T_TEST{
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
	void RotationX(float fRadian);
	void RotationY(float fRadian);
	void RotationZ(float fRadian);
	void Scale(float x, float y,float z);
	void Translation(float x, float y, float z);
	KMatrix ViewLookAt(KVector& vPosition, KVector& vTarget, KVector& vUp);
	KMatrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect);
	KMatrix OrthoLH(float w, float h, float n, float f);
	KMatrix OrthoOffCenterLH(float l, float r, float b, float t, float n, float f);
	friend 	KMatrix OrthoLH(KMatrix& mat, float w, float h, float n, float f);
	friend 	KMatrix OrthoOffCenterLH(KMatrix& mat, float l, float r, float b, float t, float n, float f);
	friend	KMatrix PerspectiveFovLH(KMatrix& mat, float fNearPlane, float fFarPlane, float fovy, float Aspect);
	friend KMatrix PerspectiveFovLH(KMatrix& mat, float fNearPlane, float fFarPlane, float fovy, float Aspect);



public:
	KMatrix operator* (KMatrix& m);

};

namespace KMath
{
	
	static KMatrix RotationX(float fRadian)
	{
		float fCosTheta = cos(fRadian);
		float fSinTheta = sin(fRadian);
		KMatrix m;
		m._22 = fCosTheta; m._23 = fSinTheta;
		m._32 = -fSinTheta; m._33 = fCosTheta;
		return m;
	}
	static KMatrix RotationY(float fRadian)
	{
		float fCosTheta = cos(fRadian);
		float fSinTheta = sin(fRadian);
		KMatrix m;
		m._11 = fCosTheta; m._13 = fSinTheta;
		m._31 = fSinTheta; m._33 = fCosTheta;
		return m;
	}
	static KMatrix RotationZ(float fRadian)
	{
		float fCosTheta = cos(fRadian);
		float fSinTheta = sin(fRadian);
		KMatrix m;
		m._11 = fCosTheta; m._12 = fSinTheta;
		m._21 = -fSinTheta; m._22 = fCosTheta;
		return m;
	}
	static KMatrix Scale(float x, float y, float z)
	{
		KMatrix m;
		m._11 = x;
		m._22 = y;
		m._33 = z;
		return m;
	}
	static KMatrix Translation(float x, float y, float z)
	{
		KMatrix m;
		m._41 = x;
		m._42 = y;
		m._43 = z;
		return m;
	}


};
};