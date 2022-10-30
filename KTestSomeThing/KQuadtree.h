#pragma once
#include "KNode.h"
#include "KMap.h"
class KQuadtree
{
public:
	KNode* m_pRootNode;
	int		m_iMaxDepth;
	KMap* m_pMap = nullptr;
public:
	bool	Create(KMap* m_pMap, int iMaxDepth = 2);
	bool	AddObject(KObject3D* pObj);
	void	BuildTree(KNode* pNode);
	bool	IsSubDivide(KNode* pNode);
	KNode* FindNode(KNode* pNode, KObject3D* pObj);
	void	Reset(KNode* pNode);
};

