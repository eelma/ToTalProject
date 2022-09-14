#include "KSpacePartition.h"
void    KSpacePartition::Create(KVector2D vPos, KVector2D vSize)
{

}
void    KSpacePartition::Create(KVector vPos, KVector vSize)
{

}
void   KSpacePartition::DynamicObjectReset()
{
}
// 1번 : 완전히 포함하는 노드에 추가하자.
// 2번 : 걸쳐만 있어도 노드에 추가하자.
void    KSpacePartition::AddStaticObject(KBaseObject* pObj)
{ 
}
void    KSpacePartition::AddDynamicObject(KBaseObject* pObj)
{  
}

KNode* KSpacePartition::FindNode(KNode* pNode, KBaseObject* pObj)
{    
    return nullptr;
}
std::vector<KBaseObject*> KSpacePartition::CollisionQuery(KBaseObject* pObj)
{
    std::vector<KBaseObject*> list;
    return list;
};

KSpacePartition::KSpacePartition()
{

}
KSpacePartition::~KSpacePartition()
{
}