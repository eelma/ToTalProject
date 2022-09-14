#pragma once
#include "KNode.h"
#include "KEnemy.h"
enum SP_TYPE
{
	K_QUADTREE,
	K_OCTREE,
	K_BSP,
};
class KSpacePartition
{
private:
	SP_TYPE     m_spType= K_OCTREE;
protected:
	KNode*		m_pRootNode;
public:
	virtual KBaseObject*    NewStaticObject(std::string name)=0;
	virtual KBaseObject* NewDynamicObject(std::string name)=0;
	virtual void    DynamicObjectReset();
public:
	virtual void    Create(KVector2D vPos, KVector2D vSize);
	virtual void    Create(KVector vPos, KVector vSize);
public:
	virtual std::vector<KBaseObject*>   CollisionQuery(KBaseObject* pObj);		
	virtual void    AddStaticObject(KBaseObject* pObj);
	virtual void    AddDynamicObject(KBaseObject* pObj);
protected:
	virtual KNode*	FindNode(KNode* pNode, KBaseObject* pObj);
public:
	KSpacePartition();
	virtual ~KSpacePartition();
};

