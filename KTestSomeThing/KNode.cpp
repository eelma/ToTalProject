#include "KNode.h"
//  0, 1
//  2, 3
KNode::KNode(KNode* pParent,KMap* pMap, DWORD dwLT, DWORD dwRT, DWORD dwRB, DWORD dwLB,DWORD dwNumCols, DWORD dwNumRows)
{
	if (pParent != nullptr)
	{
		m_iDepth = pParent->m_iDepth + 1;
	}
	m_Corner[0] = dwLT;
	m_Corner[1] = dwRT;
	m_Corner[2] = dwRB;
	m_Corner[3] = dwLB;
	m_bLeaf = false;
	m_pChild.resize(4);
	// boundingBox( aabb, obb )
	// 0  1   2   3   4
	// 5  6   7   8   9
	// 10 11  12  13  14
	// 15 16  17  18  19
	// 20  21 22  23  24

	CreateIndexBuffer(pMap, dwNumCols, dwNumRows);

}
void   KNode::CreateChildNode(KNode* pParent, KMap* pMap, DWORD dwNumCols, DWORD dwNumRows)
{
	// 0  1   2   3   4
	// 5  6   7   8   9
	// 10 11  12  13  14
	// 15 16  17  18  19
	// 20  21 22  23  24
	KRect rt = pParent->m_rt;
	DWORD dwLT = pParent->m_Corner[0]; // 0
	DWORD dwRT = pParent->m_Corner[1]; // 512
	DWORD dwLB = pParent->m_Corner[2];
	DWORD dwRB = pParent->m_Corner[3];
	DWORD dwTopCenter = (dwLT + dwRT) / 2;
	DWORD dwRightCenter = (dwRB + dwRT) / 2;
	DWORD dwBottomCenter = (dwLB + dwRB) / 2;
	DWORD dwLeftCenter = (dwLB + dwLT) / 2;
	DWORD dwCenter = (dwRT + dwLT + dwRB + dwLB) / 4;
	m_pChild[0] = new KNode(pParent, pMap, dwLT, dwTopCenter, dwLeftCenter, dwCenter, dwNumCols, dwNumRows);
	m_pChild[1] = new KNode(pParent, pMap, dwTopCenter, dwRT, dwCenter, dwRightCenter, dwNumCols, dwNumRows);
	m_pChild[2] = new KNode(pParent, pMap, dwLeftCenter, dwCenter, dwLB, dwBottomCenter, dwNumCols, dwNumRows);
	m_pChild[3] = new KNode(pParent, pMap, dwCenter, dwRightCenter, dwBottomCenter, dwRB, dwNumCols, dwNumRows);
}

KNode::~KNode()
{
	if (m_pIndexBuffer)m_pIndexBuffer->Release();

	delete m_pChild[0];
	delete m_pChild[1];
	delete m_pChild[2];
	delete m_pChild[3];
	m_pChild[0] = nullptr;
	m_pChild[1] = nullptr;
	m_pChild[2] = nullptr;
	m_pChild[3] = nullptr;
}
void KNode::CreateindexData(KMap* pMap, DWORD dwNumRows, DWORD dwNumCols)
{

	DWORD dwTL = m_Corner[0];
	DWORD dwTR = m_Corner[1];
	DWORD dwBL = m_Corner[2];
	DWORD dwBR = m_Corner[3];
	DWORD dwNumRowCell = (dwBL - dwTL) / dwNumCols;
	DWORD dwNumColCell = dwTR - dwTL;
	DWORD dwNumCells = dwNumRowCell * dwNumColCell;
	m_IndexList.resize(dwNumCells * 2 * 3);
	int iIndex = 0;

	m_kBox.vMin.x = pMap->m_VertexList[dwTL].p.x;
	m_kBox.vMin.y = 100000.0f;
	m_kBox.vMin.z = pMap->m_VertexList[dwBL].p.z;
	
	m_kBox.vMax.x = pMap->m_VertexList[dwTR].p.x;
	m_kBox.vMax.y = -100000.0f;
	m_kBox.vMax.z = pMap->m_VertexList[dwTL].p.z;

	for (int dwRow = 0; dwRow < dwNumRowCell; dwRow++)
	{
		for (int dwCol = 0; dwCol < dwNumColCell; dwCol++)
		{
			m_IndexList[iIndex + 0] = dwTL + dwCol + (dwRow * dwNumCols);
			m_IndexList[iIndex + 1] = m_IndexList[iIndex + 0] + 1;
			m_IndexList[iIndex + 2] = dwTL + dwCol + ((dwRow + 1) * dwNumCols);
			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = m_IndexList[iIndex + 2] + 1;

			for (DWORD dwVertex = 0; dwVertex < 6; dwVertex++)
			{
				if (m_kBox.vMin.y > pMap->m_VertexList[m_IndexList[iIndex + dwVertex]].p.y)
				{
					m_kBox.vMin.y = pMap->m_VertexList[m_IndexList[iIndex + dwVertex]].p.y;
				}
				if (m_kBox.vMax.y < pMap->m_VertexList[m_IndexList[iIndex + dwVertex]].p.y)
				{
					m_kBox.vMax.y = pMap->m_VertexList[m_IndexList[iIndex + dwVertex]].p.y;
				}
			}
			iIndex += 6;
		}
	}
	m_dwFace = m_IndexList.size() / 3;
	m_kBox.vCenter = (m_kBox.vMax + m_kBox.vMin) * 0.5f;
	m_kBox.vAxis[0] = { 1,0,0 };
	m_kBox.vAxis[1] = { 0,1,0 };
	m_kBox.vAxis[2] = { 0,0,1 };
	m_kBox.fExtent[0] = m_kBox.vMax.x - m_kBox.vCenter.x;
	m_kBox.fExtent[1] = m_kBox.vMax.y - m_kBox.vCenter.y;
	m_kBox.fExtent[2] = m_kBox.vMax.z - m_kBox.vCenter.z;
}
HRESULT KNode::CreateIndexBuffer(KMap* pMap, DWORD dwNumRows, DWORD dNumCols)
{
	return E_NOTIMPL;
}