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

void KMatrix::RotationX(float fRadian)
{
	Identity();
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	_22 = fCosTheta;_23 = fSinTheta;
	_32 = -fSinTheta;  _33 = fCosTheta;
}
void KMatrix::RotationY(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	_11 = fCosTheta; _13 = fSinTheta;
	_31 = fSinTheta; _33 = fCosTheta;
}
void KMatrix::RotationZ(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	_11 = fCosTheta; _12= fSinTheta;
	_21 = -fSinTheta; _22 = fCosTheta;
}
void KMatrix::Scale(float x, float y, float z)
{
	_11 = x;
	_22 = y;
	_33 = z;
}
void KMatrix::Translation(float x, float y, float z)
{
	_41 = x;
	_42 = y;
	_43 = z;
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
	_21 = vRightVector.y; _22 = vUpVector.y; _23 = vDirection.y;
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
	_44 = 0.0f;
	memcpy((void*)&ret, this, 16 * sizeof(float));
	
	
	return ret;
}
KMatrix OrthoLH(KMatrix& mat, float w, float h, float n, float f)
{
	mat.Identity();
	mat._11 = 2.0f / w;
	mat._22 = 2.0f / h;
	mat._33 = 1.0f / (f - n);
	mat._43 = n / (n - f);
	return mat;
}
KMatrix OrthoOffCenterLH(KMatrix& mat, float l, float r, float b, float t, float n, float f)
{
	mat.Identity();
	mat._11 = 2.0f / (r - l);
	mat._22 = 2.0f / (t - b);
	mat._33 = 1.0f / (f - n);
	mat._41 = (l + r) / (l - r);
	mat._42 = (t + b) / (b - t);
	mat._43 = n / (n - f);
	return mat;
}
KMatrix PerspectiveFovLH(KMatrix& mat, float fNearPlane, float fFarPlane, float fovy, float Aspect)
{
	float    h, w, Q;

	h = 1 / tan(fovy * 0.5f);  // 1/tans(x) = cot(x)
	w = h / Aspect;

	Q = fFarPlane / (fFarPlane - fNearPlane);

	mat._11 = w;
	mat._22 = h;
	mat._33 = Q;
	mat._43 = -Q * fNearPlane;
	mat._34 = 1;
	mat._44 = 0.0f;
	return mat;
}
KMatrix KMatrix::OrthoLH(float w, float h, float n, float f)
{
	Identity();
	_11 = 2.0f / w;
	_22 = 2.0f / h;
	_33 = 1.0f / (f - n);
	_43 = n / (n-f);
	return *this;
}
KMatrix KMatrix::OrthoOffCenterLH(float l, float r, float b, float t, float n, float f)
{
	Identity();
	_11 = 2.0f / (r-l);
	_22 = 2.0f / (t-b);
	_33 = 1.0f / (f - n);
	_41 = (l + r) / (l - r);
	_42 = (t + b) / (b - t);
	_43 = n / (n-f);
	return *this;
}