#pragma once
#include"KShape.h"
enum K_POSITION
{
	P_BACK = 0,
	P_FRONT,
	P_ONPLANE,
	P_SPANNING,
};
class KPlane
{
public:
	float a, b, c, d;
public:
	void Create(TVector3 v0, TVector3 v1, TVector3 v2)
	{
		TVector3 vE0 = v1 - v0;
		TVector3 vE1 = v2 - v0;
		TVector3 vNormal;// = vE0 ^ vE1;
		D3DXVec3Cross(&vNormal, &vE0, &vE1);
		a = vNormal.x;
		b = vNormal.y;
		c = vNormal.z;
		//d = -(vNormal | v0);
		d = -D3DXVec3Dot(&vNormal,&v0);
	}
	void Create(TVector3 normal, TVector3 v1)
	{
		D3DXVec3Dot(&normal, &normal);
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -D3DXVec3Dot(&normal, &v1);

	}

};
class KFrustum
{
	TMatrix* m_matView;
	TMatrix* m_matProj;
public:
	TBASIS_EX::TVector3 m_vFrustum[8];
	KPlane m_Plane[6];
public:
	void CreateFrustum(TMatrix* , TMatrix* );
	K_POSITION ClassifyPoint(TVector3 v);
	K_POSITION ClassifySphere(KSphere v);
	K_POSITION ClassifyAABB(K_AABB v);
	K_POSITION ClassifyOBB(K_OBB v);
	K_POSITION ClassifyKBOX(K_BOX v);
	

};

