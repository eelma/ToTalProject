#pragma once
#include"KObject3D.h"
class KNode
{
public:
	int						m_iDepth;
	bool					m_bLeaf;
	DWORD					m_Corner[4];
	KRect					m_rt;
	vector<KNode*>		m_pChild;
	vector<KObject3D*>	m_pStaticObjectlist;
	vector<KObject3D*>	m_pDynamicObjectlist;// ½Ç½Ã°£
public:
	void   CreateChildNode(KNode* pParent);
public:
	KNode(KNode* pParent, DWORD dwLT, DWORD dwRT, DWORD dwRB, DWORD dwLB);
	virtual ~KNode();
};

