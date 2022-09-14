#include "KOctree.h"
KBaseObject* KOctree::NewStaticObject(std::string name)
{
    KBaseObject* pObj = new KObject(name);
    return pObj;
}
KBaseObject* KOctree::NewDynamicObject(std::string name)
{
    KBaseObject* pObj = new KEnemy(name);
    return pObj;
}
std::vector<KBaseObject*> KOctree::CollisionQuery(KBaseObject* pObj)
{
    std::vector<KBaseObject*> list;
    GetCollisitionObject(m_pRootNode, pObj, list);
    return list;
};
void   KOctree::DynamicReset(KNode* pNode)
{
    if (pNode == nullptr) return;
    pNode->m_ObjectDynamicList.clear();
    for (int iChild = 0; iChild < pNode->m_pChild.size(); iChild++)
    {
        DynamicReset(pNode->m_pChild[iChild]);
    }
}
void   KOctree::DynamicObjectReset()
{
    DynamicReset(m_pRootNode);
}
void    KOctree::Create(KVector vPos, KVector vSize)
{
	m_pRootNode = CreateNode(nullptr,vPos, vSize);
	Buildtree(m_pRootNode);
}
KNode* KOctree::CreateNode(
	KNode* pParent,
	KVector vPos,
	KVector vSize)
{
	KNode* pNode = new KNode(pParent, vPos, vSize);
    pNode->m_pChild.resize(g_iMaxOctreeChild);
	return pNode;
}
void KOctree::Buildtree(KNode* pNode)
{
    if (pNode->m_iDepth >= 3) return;
    if (pNode == nullptr) return;

    KVector pos;
    KVector size;
    pos = pNode->m_Box.vMin;
    size = pNode->m_Box.vSize / 2.0f;
    pNode->m_pChild[0] = CreateNode(pNode, pos, size);
    pos.x = pNode->m_Box.vMin.x + size.x;
    pNode->m_pChild[1] = CreateNode(pNode, pos, size);
    pos.x = pNode->m_Box.vMin.x;
    pos.y = pNode->m_Box.vMin.y + size.y;
    pNode->m_pChild[2] = CreateNode(pNode, pos, size);
    pos.x = pNode->m_Box.vMin.x + size.x;
    pos.y = pNode->m_Box.vMin.y + size.y;
    pNode->m_pChild[3] = CreateNode(pNode, pos, size);

    pos.x = pNode->m_Box.vMin.x;
    pos.y = pNode->m_Box.vMin.y;
    pos.z = pNode->m_Box.vMin.z + size.z;
    pNode->m_pChild[4] = CreateNode(pNode, pos, size);
    pos.x = pNode->m_Box.vMin.x + size.x;
    pos.y = pNode->m_Box.vMin.y;
    pNode->m_pChild[5] = CreateNode(pNode, pos, size);
    pos.x = pNode->m_Box.vMin.x;
    pos.y = pNode->m_Box.vMin.y + size.y;
    pNode->m_pChild[6] = CreateNode(pNode, pos, size);
    pos.x = pNode->m_Box.vMin.x + size.x;
    pos.y = pNode->m_Box.vMin.y + size.y;
    pNode->m_pChild[7] = CreateNode(pNode, pos, size);

    for (int iChild = 0; iChild < pNode->m_pChild.size(); iChild++)
    {
        Buildtree(pNode->m_pChild[iChild]);
    }
}

bool   KOctree::IsNodeInObject(KNode* pNode, KBaseObject* pObj)
{
    return KCollision::BoxToInBox( pNode->m_Box,pObj->m_Box);
}
bool   KOctree::IsCollision(KBaseObject* pDest, KBaseObject* pSrc)
{
    if (KCollision::SphereToSphere(pDest->m_Sphere,pSrc->m_Sphere))
    {
        if (KCollision::BoxToBox(pDest->m_Box,pSrc->m_Box))
        {
            return true;
        }
    }
    return false;
}
bool   KOctree::IsCollision(KNode* pNode, KBaseObject* pSrc)
{
    if (KCollision::BoxToBox(pNode->m_Box,pSrc->m_Box))
    {
        return true;
    }
    return false;
}

void    KOctree::AddStaticObject(KBaseObject* pObj)
{
    KNode* pFindNode = FindNode(m_pRootNode, pObj);
    if (pFindNode != nullptr)
    {
        pFindNode->m_ObjectStaticList.push_back(pObj);
    }
}
void    KOctree::AddDynamicObject(KBaseObject* pObj)
{
    KNode* pFindNode = FindNode(m_pRootNode, pObj);
    if (pFindNode != nullptr)
    {
        pFindNode->m_ObjectDynamicList.push_back(pObj);
    }
}

KNode* KOctree::FindNode(KNode* pNode, KBaseObject* pObj)
{
    std::queue<KNode*> g_Queue;
    do {
        for (int iNode = 0; iNode < pNode->m_pChild.size(); iNode++)
        {
            if (pNode->m_pChild[iNode] != nullptr)
            {
                bool bIn = IsNodeInObject(pNode->m_pChild[iNode], pObj);
                if (bIn)
                {
                    g_Queue.push(pNode->m_pChild[iNode]);
                    break;
                }
            }
        }
        if (g_Queue.empty()) break;
        pNode = g_Queue.front();
        g_Queue.pop();
    } while (pNode);
    return pNode;
}
void  KOctree::GetCollisitionObject(KNode* pNode,
    KBaseObject* pSrcObject,
    std::vector<KBaseObject*>& list)
{
    if (pNode == nullptr) return;
    for (int iObj = 0; iObj < pNode->m_ObjectStaticList.size(); iObj++)
    {
        if (IsCollision(pNode->m_ObjectStaticList[iObj], pSrcObject))
        {
            list.push_back(pNode->m_ObjectStaticList[iObj]);
        }
    }
    for (int iObj = 0; iObj < pNode->m_ObjectDynamicList.size(); iObj++)
    {
        if (IsCollision(pNode->m_ObjectDynamicList[iObj], pSrcObject))
        {
            list.push_back(pNode->m_ObjectDynamicList[iObj]);
        }
    }
    if (pNode->m_pChild[0] != nullptr)
    {
        for (int iChild = 0; iChild < pNode->m_pChild.size(); iChild++)
        {
            if (IsCollision(pNode->m_pChild[iChild], pSrcObject))
            {
                GetCollisitionObject(pNode->m_pChild[iChild], pSrcObject, list);
            }
        }
    }
}
