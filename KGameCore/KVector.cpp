#include "KVector.h"
#include"KMatrix.h"
namespace T_TEST
{
	KVector2::KVector2()
	{
		x = y = 0.0f;
	}
	KVector2::KVector2(float x, float y)
	{
		v[0] = x;
		v[1] = y;
	}
	KVector2::KVector2(const KVector2& v)
	{
		x = v.x;
		y = v.y;
	}
	KVector2 KVector2::operator + (KVector2& v)
	{
		return KVector2(x + v.x, y + v.y);
	}
	KVector2 KVector2::operator - (KVector2& v)
	{
		return KVector2(x - v.x, y - v.y);
	}
	KVector2 KVector2::operator * (float scala)
	{
		return KVector2(x * scala, y * scala);
	}
	KVector2 KVector2::operator / (float scala)
	{
		return KVector2(x / scala, y / scala);
	}
	KVector2 KVector2::operator *= (float scala)
	{
		x *= scala;
		y *= scala;
		return *this;
	}
	KVector2 KVector2::operator += (KVector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	KVector2 KVector2::operator -= (KVector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	bool      KVector2::operator == (KVector2& v)
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
	bool      KVector2::operator <= (KVector2& b)
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
	bool      KVector2::operator >= (KVector2& b)
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
	float KVector2::LengthSquared()
	{
		return (x * x + y * y);
	}

	float KVector2::Length()
	{
		return sqrt(LengthSquared());
	}
	// 정규화 -> 단위벡터(자신을) 계산
	void KVector2::Normalized()
	{
		float fInvertLength = 1.0f / Length();
		x = x * fInvertLength;
		y = y * fInvertLength;
	}
	// 단위벡터 반환
	KVector2 KVector2::Identity()
	{
		KVector2 ret = *this;
		float fInvertLength = 1.0f / Length();
		ret.x = ret.x * fInvertLength;
		ret.y = ret.y * fInvertLength;
		return ret;
	}
	float     KVector2::Angle(KVector2& v)
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
		return KVector(x + v.x, y + v.y, z + v.z);
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
		return (x * x + y * y + z * z);
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
	float KVector::operator | (KVector const& v0)
	{
		return x * v0.x + y * v0.y + z * v0.z;
	}
	KVector KVector::operator ^ (KVector const& v0)
	{
		return KVector((y * v0.z - z * v0.y), (z * v0.x - x * v0.z), (x * v0.y - y * v0.x));
	}

	KVector4::KVector4()
	{
		x = y = z = w = 0.0f;
	}
	KVector4::KVector4(float x, float y, float z, float w)
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
	}
	KVector4::KVector4(const KVector4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	KVector4 KVector4::operator + (KVector4& v)
	{
		return KVector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	KVector4 KVector4::operator - (KVector4& v)
	{
		return KVector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	KVector4 KVector4::operator * (float scala)
	{
		return KVector4(x * scala, y * scala, z * scala, w * scala);
	}
	KVector4 KVector4::operator / (float scala)
	{
		return KVector4(x / scala, y / scala, z / scala, w / scala);
	}
	KVector4 KVector4::operator *= (float scala)
	{
		x *= scala;
		y *= scala;
		z *= scala;
		w *= scala;
		return *this;
	}
	KVector4 KVector4::operator += (KVector4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	KVector4 KVector4::operator -= (KVector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	bool      KVector4::operator == (KVector4& v)
	{
		if (fabs(x - v.x) < T_Epsilon)
		{
			if (fabs(y - v.y) < T_Epsilon)
			{
				if (fabs(z - v.z) < T_Epsilon)
				{
					if (fabs(w - v.w) < T_Epsilon)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	bool      KVector4::operator <= (KVector4& b)
	{
		if (x <= b.x)
		{
			if (y <= b.y)
			{
				if (z <= b.z)
				{
					if (w <= b.w)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	bool      KVector4::operator >= (KVector4& b)
	{
		if (x >= b.x)
		{
			if (y >= b.y)
			{
				if (z >= b.z)
				{
					if (w >= b.w)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	float KVector4::LengthSquared()
	{
		return (x * x + y * y + z * z + w * w);
	}

	float KVector4::Length()
	{
		return sqrt(LengthSquared());
	}
	// 정규화 -> 단위벡터(자신을) 계산
	void KVector4::Normalized()
	{
		float fInvertLength = 1.0f / Length();
		x = x * fInvertLength;
		y = y * fInvertLength;
		z = z * fInvertLength;
		w = w * fInvertLength;
	}
	// 단위벡터 반환
	KVector4 KVector4::Identity()
	{
		KVector4 ret = *this;
		float fInvertLength = 1.0f / Length();
		ret.x = ret.x * fInvertLength;
		ret.y = ret.y * fInvertLength;
		ret.z = ret.z * fInvertLength;
		ret.w = ret.w * fInvertLength;
		return ret;
	}
	float     KVector4::Angle(KVector4& v)
	{
		float fCos = x * v.x + y * v.y + z * v.z + w * v.w;//내적
		fCos = fCos / (Length() * v.Length());
		float fRadian = acos(fCos);
		float fDegree = RadianToDegree(fRadian);
		return fDegree;
	}
	KVector  KVector::operator* (KMatrix& m)
	{
		KVector v;
		v.x = x * m._11 + y * m._21 + z * m._31 + 1.0f * m._41;
		v.y = x * m._12 + y * m._22 + z * m._32 + 1.0f * m._42;
		v.z = x * m._13 + y * m._23 + z * m._33 + 1.0f * m._43;
		return v;
	}
	KVector KVector::Normal()
	{
		KVector ret = *this;
		float fInvertLength = 1.0f / Length();
		ret.x = ret.x * fInvertLength;
		ret.y = ret.y * fInvertLength;
		ret.z = ret.z * fInvertLength;
		return ret;
	}
};