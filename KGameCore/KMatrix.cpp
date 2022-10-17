#include "KMatrix.h"
KMatrix3x3::KMatrix3x3()
{
	Identity();
}
void KMatrix3x3::Identity()
{
	_12 = _13 = 0.f;
	_21 = _23 = 0.0f;
	_31 = _32 = 0.0f;
	_11 = _22 = _33 = 1.0f;
}
KMatrix3x3 KMatrix3x3::Transpose()
{

	KMatrix3x3 m;
	m._11 = _11; m._12 = _21; m._13 = _31;
	m._21 = _12; m._22 = _22; m._23 = _32;
	m._31 = _13; m._32 = _23; m._33 = _33;
	return m;

}
KMatrix3x3 KMatrix3x3::Scale(float x, float y)
{
	KMatrix3x3 m;
	m._11 = x;
	m._22 = y;
	return m;
}
KMatrix3x3 KMatrix3x3::Translation(float x, float y)
{
	KMatrix3x3 m;
	m._31 = x;
	m._32 = y;
	return m;
}
KMatrix3x3 KMatrix3x3::operator*(KMatrix3x3& matrix)
{
	KMatrix3x3 mat;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mat.m[j][i] =
				m[j][0] * matrix.m[0][i] +
				m[j][1] * matrix.m[0][i] +
				m[j][2] * matrix.m[0][i];
		}
	}
	return mat;
}

KMatrix::KMatrix()
{
	Identity();
}
void KMatrix::Identity()
{
	_12 = _13 = _14 = 0.0f;
	_21 = _23 = _24 = 0.0f;
	_31 = _32 = _34 = 0.0f;
	_41 = _42 = _43 = 0.0f;
	_11 = _22 = _33 = _44 = 1.0f;
}
KMatrix KMatrix::Transpose()
{
	KMatrix m;
	m._11 = _11; m._12 = _21; m._13 = _31; m._14 = _41;
	m._21 = _12; m._22 = _22; m._23 = _32; m._24 = _42;
	m._31 = _13; m._32 = _23; m._33 = _33; m._34 = _43;
	m._41 = _14; m._42 = _24; m._43 = _34; m._44 = _44;
	return m;
}

KMatrix KMatrix::RotationX(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	KMatrix m;
	m._22 = fCosTheta; m._23 = fSinTheta;
	m._32 = -fSinTheta; m._33 = fCosTheta;
	return m;
}
KMatrix KMatrix::RotationY(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	KMatrix m;
	m._11 = fCosTheta; m._13 = fSinTheta;
	m._31 = fSinTheta; m._33 = fCosTheta;
	return m;
}
KMatrix KMatrix::RotationZ(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	KMatrix m;
	m._11 = fCosTheta; m._12= fSinTheta;
	m._21 = -fSinTheta; m._22 = fCosTheta;
	return m;
}
KMatrix KMatrix::Scale(float x, float y, float z)
{
	KMatrix m;
	m._11 = x;
	m._22 = y;
	m._33 = z;
	return m;
}
KMatrix KMatrix::Translation(float x, float y, float z)
{
	KMatrix m;
	m._41 = x;
	m._42 = y;
	m._43 = z;
	return m;
}
KMatrix KMatrix::operator*(KMatrix& matrix)
{
	KMatrix mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[j][i] =
				m[j][0] * matrix.m[0][i] +
				m[j][1] * matrix.m[1][i] +
				m[j][2] * matrix.m[2][i] +
				m[j][3] * matrix.m[3][i];
		}
	}
	return mat;
}

KMatrix KMatrix::ViewLookAt(KVector& vPosition, KVector& vTarget, KVector& vUp)
{
	KMatrix matrix;
	KVector vDirection = (vTarget - vPosition).Normal();
	KVector vRightVector = (vUp ^ vDirection).Normal();
	KVector vUpVector = (vDirection ^ vRightVector).Normal();

	_11 = vRightVector.x; _12 = vUpVector.x; _13 = vDirection.x;
	_21 = vRightVector.y; _12 = vUpVector.y; _23 = vDirection.y;
	_31 = vRightVector.z; _32 = vUpVector.z; _33 = vDirection.z;

	_41 = -(vPosition.x * _11 + vPosition.y * _21 + vPosition.z * _31);
	_42 = -(vPosition.x * _12 + vPosition.y * _22 + vPosition.z * _32);
	_43 = -(vPosition.x * _13 + vPosition.y * _23 + vPosition.z * _33);
	memcpy(&matrix, this, 16*sizeof(float));
	return matrix;
}
KMatrix KMatrix::PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect)
{
	float h, w, Q;
	h = 1 / tan(fovy * 0.5f);
	w = h / Aspect;
	Q = fFarPlane / (fFarPlane - fNearPlane);
	KMatrix ret;
	ZeroMemory(this, sizeof(KMatrix));
	_11 = w;
	_22 = h;
	_33 = Q;
	_43 = -Q * fNearPlane;
	_34 = 1;
	memcpy((void*)&ret, this, 16 * sizeof(float));
	
	
	return ret;
}
