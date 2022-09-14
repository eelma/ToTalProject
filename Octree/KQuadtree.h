#pragma once
#include "KSpacePartition.h"
static const int g_iMaxQuadtreeChild = 4;
class KQuadtree : public KSpacePartition
{
public:
    KBaseObject* NewStaticObject(std::string name)override;
    KBaseObject* NewDynamicObject(std::string name)override;
    void    DynamicObjectReset()override;;
    void    Create(KVector2D vPos, KVector2D vSize) override;
    void    AddStaticObject(KBaseObject* pObj)override;
    void    AddDynamicObject(KBaseObject* pObj)override;
    KNode*  FindNode(KNode* pNode, KBaseObject* pObj)override;
    std::vector<KBaseObject*> CollisionQuery(KBaseObject* pObj)override;
protected: 
    void    DynamicReset(KNode* pNode);    
    KNode*  CreateNode(KNode* pParent, KVector2D vPos, KVector2D vSize);
    void    Buildtree(KNode* pNode);
    void    GetCollisitionObject(KNode* pNode,    KBaseObject* obj,
                                    std::vector<KBaseObject*>& list);    
    bool    IsNodeInObject(KNode* pNode, KBaseObject* pObj);
public:
    KQuadtree();
    virtual ~KQuadtree();
};