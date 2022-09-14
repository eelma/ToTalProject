#pragma once
#include "KSpacePartition.h"

static const int g_iMaxOctreeChild = 8;
class KOctree :  public KSpacePartition
{	
public:
	KBaseObject* NewStaticObject(std::string name)override;
	KBaseObject* NewDynamicObject(std::string name)override;
	void    DynamicObjectReset()override;;	
	void    Create(KVector vPos, KVector vSize) override;
	void    AddStaticObject(KBaseObject* pObj)override;
	void    AddDynamicObject(KBaseObject* pObj)override;
	KNode*  FindNode(KNode* pNode, KBaseObject* pObj)override;
	std::vector<KBaseObject*> CollisionQuery(KBaseObject* pObj)override;
public:
	void    DynamicReset(KNode* pNode);	
	bool    IsNodeInObject(KNode* pNode, KBaseObject* pObj);
	bool    IsCollision(KBaseObject* pDest, KBaseObject* pSrc);
	bool	IsCollision(KNode* pNode, KBaseObject* pSrc);
	KNode*	CreateNode(KNode* pParent,KVector vPos,KVector vSize);
	void	Buildtree(KNode* pNode);	
    void    GetCollisitionObject(KNode* pNode,KBaseObject* pSrcObject,
								 std::vector<KBaseObject*>& list);
};

