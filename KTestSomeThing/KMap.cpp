#include "KMap.h"
bool KMap::Build(UINT iWidth, UINT iHeight)
{
	//전체 셀 개수 = (iWidth)*(iHeight)
	//전체 페이스 개수 = (iWidth)*(iHeight)*2
	//전체 정점 개수 = iWidth * iHeight
	m_dwNumRows = iWidth;
	m_dwNumColumns = iHeight;
	m_VertexList.resize(iWidth * iHeight);
	int iHalfWidth = iWidth / 2;
	int iHalfHeight = iHeight / 2;
	float fCellDistance = 1.0f;
	for (int iRow = 0; iRow < iHeight; iRow++)
	{
		for (int iCol = 0; iCol < iHeight; iCol++)
		{
			m_VertexList[iRow * iWidth + iCol].p =
			
			//{(float)iCol, 0.0f, (float)iHeight-iRow};
			{(float)(iCol-iHalfWidth)*fCellDistance, cosf(DegreeToRadian(iCol))*20.0f+sinf(DegreeToRadian(iRow))*20.0f,
			(float)(iHalfHeight-iRow)*fCellDistance};

			m_VertexList[iRow * iWidth + iCol].c = { 1,1,1,1 };
			m_VertexList[iRow * iWidth + iCol].t =
				{(float)(iCol) / (float)(iWidth - 1) * 10.0f,(float)(iRow) / (float)(iHeight - 1) * 10.0f};		
		}
	}

	m_IndexList.resize((iWidth - 1) * (iHeight - 1) * 2 * 3.0f);
	UINT iIndex = 0;
	for (int iRow = 0; iRow < iHeight - 1; iRow++)
	{
		for (int iCol = 0; iCol < iWidth - 1; iCol++)
		{
			UINT iNextRow = iRow + 1;
			UINT iNextCol = iCol + 1;
			m_IndexList[iIndex + 0] = iRow * iWidth + iCol;
			m_IndexList[iIndex + 1] = m_IndexList[iIndex+0]+1;
			m_IndexList[iIndex + 2] = iNextRow * iWidth + iCol;

			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = m_IndexList[iIndex + 3] + 1;

			iIndex += 6;
		}
	}
	indexlist.resize(m_IndexList.size());
	m_dwFace = m_IndexList.size() / 3;
	return true;
}

bool KMap::UpdateBuffer(KCameraDebug* pMainCamera)
{
	m_dwFace = 0;
	DWORD index = 0;
	KVector v[3];
	for (int i = 0; i < m_IndexList.size() / 3; i++)
	{
		UINT i0 = m_IndexList[i * 3 + 0];
		UINT i1 = m_IndexList[i * 3 + 1];
		UINT i2 = m_IndexList[i * 3 + 2];

		v[0] = m_VertexList[i0].p;
		v[1] = m_VertexList[i1].p;
		v[2] = m_VertexList[i2].p;

		for (int i = 0; i < 3; i++)
		{
			bool bRender = pMainCamera->m_vFrustum.ClassifyPoint(v[i]);
			if (bRender)
			{

				indexlist[index++] = i0;
				indexlist[index++] = i1;
				indexlist[index++] = i2;
				m_dwFace++;
				break;
			}
		}
	}
	m_pImmediateContext->UpdateSubresource(
		m_pIndexBuffer, 0, nullptr, &indexlist.at(0), 0, 0);

	return true;
}
