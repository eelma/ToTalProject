#include "KFrustum.h"
void KFrustum::CreateFrustum(KMatrix* matView, KMatrix*matProj)
{

	TBASIS_EX::TMatrix view = *(TBASIS_EX::TMatrix*)matView;
	TBASIS_EX::TMatrix proj = *(TBASIS_EX::TMatrix*)matProj;
	TBASIS_EX::TMatrix matInvViewProj = view * proj;
	TBASIS_EX::D3DXMatrixInverse(&matInvViewProj, NULL, &matInvViewProj);

	m_vFrustum[0] = TBASIS_EX::TVector3(-1.0f,-1.0f,0.0f);
	m_vFrustum[1] = TBASIS_EX::TVector3(-1.0f, 1.0f,0.0f);
	m_vFrustum[2] = TBASIS_EX::TVector3(1.0f, 1.0f,0.0f);
	m_vFrustum[3] = TBASIS_EX::TVector3(1.0f,-1.0f,0.0f);
	m_vFrustum[4] = TBASIS_EX::TVector3(-1.0f,-1.0f,1.0f);
	m_vFrustum[5] = TBASIS_EX::TVector3(-1.0f,1.0f,1.0f);
	m_vFrustum[6] = TBASIS_EX::TVector3(1.0f,1.0f,1.0f);
	m_vFrustum[7] = TBASIS_EX::TVector3(1.0f,-1.0f,1.0f);

	for (int iVer = 0; iVer < 8; iVer++)
	{
		TBASIS_EX::D3DXVec3TransformCoord(
			&m_vFrustum[iVer], &m_vFrustum[iVer], &matInvViewProj);
	}
	//5    6
	//4    7
	//->   <-
	//1    2
	//0    3
	m_Plane[0].Create(*((KVector*)&m_vFrustum[1]),
					  *((KVector*)&m_vFrustum[5]), 
					  *((KVector*)&m_vFrustum[0]));//left
	m_Plane[1].Create(*((KVector*)&m_vFrustum[3]),
					  *((KVector*)&m_vFrustum[6]),
					  *((KVector*)&m_vFrustum[2]));//right
	m_Plane[2].Create(*((KVector*)&m_vFrustum[5]),
					  *((KVector*)&m_vFrustum[2]),
					  *((KVector*)&m_vFrustum[6]));//top
	m_Plane[3].Create(*((KVector*)&m_vFrustum[0]),
					  *((KVector*)&m_vFrustum[7]),
					  *((KVector*)&m_vFrustum[3]));//bottom
	m_Plane[4].Create(*((KVector*)&m_vFrustum[0]),
					  *((KVector*)&m_vFrustum[2]),
					  *((KVector*)&m_vFrustum[1]));//near
	m_Plane[5].Create(*((KVector*)&m_vFrustum[5]),
					  *((KVector*)&m_vFrustum[6]),
					  *((KVector*)&m_vFrustum[4]));//far

}
bool KFrustum::ClassifyPoint(KVector v)
{
	for (int i = 0; i < 6; i++)
	{
		float fDistance =
			m_Plane[i].a * v.x +
			m_Plane[i].b * v.y +
			m_Plane[i].c * v.z +
			m_Plane[i].d;
		if (fDistance < 0)return false;

	}
	return true;

}

bool KFrustum::ClassifySphere(KSphere v)
{

	return true;
}

bool KFrustum::ClassifyAABB(K_AABB v)
{
	return true;
}

bool KFrustum::ClassifyOBB(K_OBB v)
{
	return true;
}

bool KFrustum::ClassifyKBOX(K_BOX v)
{
	return true;
}
