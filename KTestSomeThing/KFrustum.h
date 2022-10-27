#pragma once
#include"KShape.h"

class KPlane
{
public:
	float a, b, c, d;
public:
	void Create(KVector v0, KVector v1, KVector v2)
	{
		KVector vE0 = v1 - v0;
		KVector vE1 = v2 - v0;
		KVector vNormal = vE0 ^ vE1;
		vNormal.Normalized();
		a = vNormal.x;
		b = vNormal.y;
		c = vNormal.z;
		d = -(vNormal | v0);

	}
	void Create(KVector normal, KVector v1)
	{
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -(normal | v1);
	}

};
class KFrustum
{
	KMatrix* m_matView;
	KMatrix* m_matProj;
public:
	TBASIS_EX::TVector3 m_vFrustum[8];
	KPlane m_Plane[6];
public:
	void CreateFrustum(KMatrix* , KMatrix* );
	bool ClassifyPoint(KVector v);
	bool ClassifySphere(KSphere v);
	bool ClassifyAABB(K_AABB v);
	bool ClassifyOBB(K_OBB v);
	bool ClassifyKBOX(K_BOX v);
	

};

