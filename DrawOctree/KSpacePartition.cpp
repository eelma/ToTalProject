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
// 1�� : ������ �����ϴ� ��忡 �߰�����.
// 2�� : ���ĸ� �־ ��忡 �߰�����.
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