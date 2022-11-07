#include "KFrustum.h"
void KFrustum::CreateFrustum(TMatrix* matView, TMatrix*matProj)
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
	m_Plane[0].Create(*((TVector3*)&m_vFrustum[1]),
					  *((TVector3*)&m_vFrustum[5]), 
					  *((TVector3*)&m_vFrustum[0]));//left
	m_Plane[1].Create(*((TVector3*)&m_vFrustum[3]),
					  *((TVector3*)&m_vFrustum[6]),
					  *((TVector3*)&m_vFrustum[2]));//right
	m_Plane[2].Create(*((TVector3*)&m_vFrustum[5]),
					  *((TVector3*)&m_vFrustum[2]),
					  *((TVector3*)&m_vFrustum[6]));//top
	m_Plane[3].Create(*((TVector3*)&m_vFrustum[0]),
					  *((TVector3*)&m_vFrustum[7]),
					  *((TVector3*)&m_vFrustum[3]));//bottom
	m_Plane[4].Create(*((TVector3*)&m_vFrustum[2]),
					  *((TVector3*)&m_vFrustum[1]),
					  *((TVector3*)&m_vFrustum[0]));//near
	m_Plane[5].Create(*((TVector3*)&m_vFrustum[5]),
					  *((TVector3*)&m_vFrustum[6]),
					  *((TVector3*)&m_vFrustum[4]));//far

}
K_POSITION KFrustum::ClassifyPoint(TVector3 v)
{
	for (int i = 0; i < 6; i++)
	{
		float fDistance =
			m_Plane[i].a * v.x +
			m_Plane[i].b * v.y +
			m_Plane[i].c * v.z +
			m_Plane[i].d;
		if (fDistance == 0)return P_ONPLANE;
		if (fDistance < 0)return P_FRONT;

	}
	return P_BACK;

}

K_POSITION KFrustum::ClassifySphere(KSphere v)
{

	return P_SPANNING;
}

K_POSITION KFrustum::ClassifyAABB(K_AABB v)
{
	return P_SPANNING;
}

K_POSITION KFrustum::ClassifyOBB(K_OBB v)
{
	return P_SPANNING;
}

K_POSITION KFrustum::ClassifyKBOX(K_BOX box)
{
	float fPlaneToCenter = 0.0;
	float fDistance = 0.0f;
	TVector3 vDir;
	K_POSITION k_Position;
	k_Position = P_FRONT;

	for (int iplane = 0; iplane < 6; iplane++)
	{

		vDir = box.vAxis[0] * box.fExtent[0];
		fDistance = fabs(m_Plane[iplane].a * vDir.x + m_Plane[iplane].b * vDir.y + m_Plane[iplane].c * vDir.z);
		vDir = box.vAxis[1] * box.fExtent[1];
		fDistance += fabs(m_Plane[iplane].a * vDir.x + m_Plane[iplane].b * vDir.y + m_Plane[iplane].c * vDir.z);
		vDir = box.vAxis[2] * box.fExtent[2];
		fDistance += fabs(m_Plane[iplane].a * vDir.x + m_Plane[iplane].b * vDir.y + m_Plane[iplane].c * vDir.z);

		fPlaneToCenter = m_Plane[iplane].a * box.vCenter.x + m_Plane[iplane].b * box.vCenter.y + m_Plane[iplane].c * box.vCenter.z + m_Plane[iplane].d;

		if (fPlaneToCenter > 0)
		{
			if (fPlaneToCenter < fDistance)
			{
				k_Position = P_SPANNING;
				break;
			}
		}
		else
			if (fPlaneToCenter < 0)
			{
				k_Position = P_BACK;
				if(fPlaneToCenter> -fDistance)
				{ 
				k_Position = P_SPANNING;
				}
				break;
			}
	
	}

	return k_Position;
}
