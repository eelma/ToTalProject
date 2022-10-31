#pragma once
#include"KObject3D.h"
#include"KMap.h"
class KNode
{
public:
	int					m_iDepth;
	bool				m_bLeaf;
	DWORD				m_Corner[4];
	KRect				m_rt;
	DWORD				m_dwFace;
	K_BOX				m_kBox;
	vector<DWORD>		m_IndexList;
	ID3D11Buffer*		m_pIndexBuffer;

	vector<KNode*>		m_pChild;
	vector<KObject3D*>	m_pStaticObjectlist;
	vector<KObject3D*>	m_pDynamicObjectlist;// ½Ç½Ã°£
public:
	void   CreateChildNode(KNode* pParent, KMap* pMap, DWORD dwNumCols, DWORD dwNumPows);
	void CreateindexData(KMap* pMap, DWORD dwNumRows, DWORD dNumCols);
	HRESULT CreateIndexBuffer(KMap* pMap, DWORD dwNumRows, DWORD dNumCols);
public:
	KNode(KNode* pParent,KMap* pMpap, DWORD dwLT, DWORD dwRT, DWORD dwRB, DWORD dwLB,
			DWORD dwRows, DWORD dwCols);
	virtual ~KNode();
};

