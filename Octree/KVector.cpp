#include "KVector.h"
KVector2D::KVector2D()
{
	x = y = 0.0f;
}
KVector2D::KVector2D(float x, float y)
{
	v[0] = x;
	v[1] = y;
}
KVector2D::KVector2D(const KVector2D& v)
{
	x = v.x;
	y = v.y;
}
KVector2D KVector2D::operator + (KVector2D& v)
{
	return KVector2D(x + v.x, y + v.y);
}
KVector2D KVector2D::operator - (KVector2D& v)
{
	return KVector2D(x - v.x, y - v.y);
}
KVector2D KVector2D::operator * (float scala)
{
	return KVector2D(x *scala, y * scala);
}
KVector2D KVector2D::operator / (float scala)
{
	return KVector2D(x / scala, y / scala);
}
KVector2D KVector2D::operator *= (float scala)
{
	x *= scala;
	y *= scala;
	return *this;
}
KVector2D KVector2D::operator += (KVector2D& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
KVector2D KVector2D::operator -= (KVector2D& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
bool      KVector2D::operator == (KVector2D& v)
{
	if (fabs(x - v.x) < T_Epsilon)
	{
		if (fabs(y - v.y) < T_Epsilon)
		{
			return true;
		}
	}
	return false;
}
bool      KVector2D::operator <= (KVector2D& b)
{
	if (x <= b.x)
	{
		if (y <= b.y)
		{
			return true;
		}
	}
	return false;
}
bool      KVector2D::operator >= (KVector2D& b)
{
	if (x >= b.x)
	{
		if (y >= b.y)
		{
			return true;			
		}
	}
	return false;
}
float KVector2D::LengthSquared()
{
	return (x*x + y*y);
}

float KVector2D::Length()
{
	return sqrt(LengthSquared());
}
// 정규화 -> 단위벡터(자신을) 계산
void KVector2D::Normalized()
{
	float fInvertLength = 1.0f/ Length();
	x = x * fInvertLength;
	y = y * fInvertLength;
}
// 단위벡터 반환
KVector2D KVector2D::Identity()
{
	KVector2D ret = *this;
	float fInvertLength = 1.0f / Length();
	ret.x = ret.x * fInvertLength;
	ret.y = ret.y * fInvertLength;
	return ret;
}
float     KVector2D::Angle(KVector2D& v)
{
	float fCos = x * v.x + y * v.y;//내적
	fCos = fCos / (Length() * v.Length());
	float fRadian = acos(fCos);
	float fDegree = RadianToDegree(fRadian);
	return fDegree;
}


///// 3d
KVector::KVector()
{
	x = y = z = 0.0f;
}
KVector::KVector(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}
KVector::KVector(const KVector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
KVector KVector::operator + (KVector& v)
{
	return KVector(x + v.x, y + v.y, z+ v.z);
}
KVector KVector::operator - (KVector& v)
{
	return KVector(x - v.x, y - v.y, z - v.z);
}
KVector KVector::operator * (float scala)
{
	return KVector(x * scala, y * scala, z * scala);
}
KVector KVector::operator / (float scala)
{
	return KVector(x / scala, y / scala, z / scala);
}
KVector KVector::operator *= (float scala)
{
	x *= scala;
	y *= scala;
	z *= scala;
	return *this;
}
KVector KVector::operator += (KVector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
KVector KVector::operator -= (KVector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
bool      KVector::operator <= (KVector& b)
{
	if (fabs(x - b.x) <= T_Epsilon)
	{
		if (fabs(y - b.y) <= T_Epsilon)
		{
			if (fabs(z - b.z) <= T_Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}
bool      KVector::operator >= (KVector& b)
{
	if (fabs(x - b.x) >= T_Epsilon)
	{
		if (fabs(y - b.y) >= T_Epsilon)
		{
			if (fabs(z - b.z) >= T_Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}
bool      KVector::operator == (KVector& v)
{
	if (fabs(x - v.x) < T_Epsilon)
	{
		if (fabs(y - v.y) < T_Epsilon)
		{
			if (fabs(z - v.z) < T_Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}

float KVector::LengthSquared()
{
	return (x * x + y * y + z*z);
}

float KVector::Length()
{
	return sqrt(LengthSquared());
}
// 정규화 -> 단위벡터(자신을) 계산
void KVector::Normalized()
{
	float fInvertLength = 1.0f / Length();
	x = x * fInvertLength;
	y = y * fInvertLength;
	z = z * fInvertLength;
}
// 단위벡터 반환
KVector KVector::Identity()
{
	KVector ret = *this;
	float fInvertLength = 1.0f / Length();
	ret.x = ret.x * fInvertLength;
	ret.y = ret.y * fInvertLength;
	ret.z = ret.z * fInvertLength;
	return ret;
}
float     KVector::Angle(KVector& v)
{
	float fCos = x * v.x + y * v.y + z * v.z;//내적
	fCos = fCos / (Length() * v.Length());
	float fRadian = acos(fCos);
	float fDegree = RadianToDegree(fRadian);
	return fDegree;
}

