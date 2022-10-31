#pragma once
#include "KNode.h"
#include "KMap.h"
class KQuadtree
{
public:
	KNode* m_pRootNode;
	int		m_iMaxDepth;
	KMap* m_pMap = nullptr;
	KCamera* m_pCamera = nullptr;
	vector<KNode*>m_pLeafNodeList;
	vector<KNode*>m_pDrawLeafNodeList;
public:
	bool	Create(KCamera* pMainCamera, KMap* m_pMap, int iMaxDepth = 3);
	bool	AddObject(KObject3D* pObj);
	void	BuildTree(KNode* pNode);
	bool	IsSubDivide(KNode* pNode);
	KNode* FindNode(KNode* pNode, KObject3D* pObj);
	void	Reset(KNode* pNode);
	bool Frame();
	bool Render();
	KNode* VisibleNode(KNode* pNode);
	virtual ~KQuadtree();                        
};

