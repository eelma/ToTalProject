#include "KQuadtree.h"
KBaseObject* KQuadtree::NewStaticObject(std::string name)
{
    KBaseObject* pObj = new KObject2D(name);
    return pObj;
}
KBaseObject* KQuadtree::NewDynamicObject(std::string name)
{
    KBaseObject* pObj = new KEnemy2D(name);
    return pObj;
}
void    KQuadtree::AddStaticObject(KBaseObject* pObj)
{
    KNode* pFindNode = FindNode(m_pRootNode, pObj);
    if (pFindNode != nullptr)
    {
        pFindNode->m_ObjectStaticList.push_back(pObj);
    }
}
void    KQuadtree::AddDynamicObject(KBaseObject* pObj)
{
    KNode* pFindNode = FindNode(m_pRootNode, pObj);
    if (pFindNode != nullptr)
    {
        pFindNode->m_ObjectDynamicList.push_back(pObj);
    }
}
KNode* KQuadtree::FindNode(KNode* pNode, KBaseObject* pObj)
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
void   KQuadtree::DynamicReset(KNode* pNode)
{
    if (pNode == nullptr) return;
    pNode->m_ObjectDynamicList.clear();
    for (int iChild = 0; iChild < pNode->m_pChild.size(); iChild++)
    {
        DynamicReset(pNode->m_pChild[iChild]);
    }    
}
void    KQuadtree::DynamicObjectReset()
{
    DynamicReset(m_pRootNode);
}
void KQuadtree::Create(KVector2D vPos, KVector2D vSize)
{
    m_pRootNode = CreateNode(nullptr, vPos, vSize);
    Buildtree(m_pRootNode);
}
void KQuadtree::Buildtree(KNode* pNode)
{
    if (pNode->m_iDepth >= 2) return;
    if (pNode == nullptr) return;

    KVector2D p, s;
    p.x = pNode->m_rt.x1;
    p.y = pNode->m_rt.y1;
    s.x = pNode->m_rt.w / 2.0f;
    s.y = pNode->m_rt.h / 2.0f;
    pNode->m_pChild[0] = CreateNode(pNode, p, s);
    p.x = pNode->m_rt.x1 + s.x;
    p.y = pNode->m_rt.y1;
    pNode->m_pChild[1] = CreateNode(pNode, p, s);
    p.x = pNode->m_rt.x1;
    p.y = pNode->m_rt.y1 + s.y;
    pNode->m_pChild[2] = CreateNode(pNode, p, s);
    p.x = pNode->m_rt.x1 + s.x;
    p.y = pNode->m_rt.y1 + s.y;
    pNode->m_pChild[3] = CreateNode(pNode, p, s);

    for (int iChild = 0; iChild < g_iMaxQuadtreeChild; iChild++)
    {
        Buildtree(pNode->m_pChild[iChild]);
    }
}
KNode* KQuadtree::CreateNode(
    KNode* pParent,
    KVector2D vPos,
    KVector2D vSize)
{
    KNode* pNode = new KNode(pParent, vPos, vSize);
    pNode->m_pChild.resize(g_iMaxQuadtreeChild);
    return pNode;
}


std::vector<KBaseObject*> KQuadtree::CollisionQuery(KBaseObject* pObj)
{
    std::vector<KBaseObject*> list;
    GetCollisitionObject(this->m_pRootNode, pObj, list);
    return list;
};
void  KQuadtree::GetCollisitionObject(KNode* pNode,
    KBaseObject* pSrcObject,
    std::vector<KBaseObject*>& list)
{
    if (pNode == nullptr) return;
    for (int iObj = 0; iObj < pNode->m_ObjectStaticList.size(); iObj++)
    {
        if (KCollision::RectToRect(
            pNode->m_ObjectStaticList[iObj]->m_rt,
            pSrcObject->m_rt))
        {
            list.push_back(pNode->m_ObjectStaticList[iObj]);
        }
    }
   for (int iObj = 0; iObj < pNode->m_ObjectDynamicList.size(); iObj++)
    {

       if (KCollision::RectToRect(
           pNode->m_ObjectDynamicList[iObj]->m_rt,
           pSrcObject->m_rt))
       {
           list.push_back(pNode->m_ObjectDynamicList[iObj]);
       }

        /*if (KCollision::CircleToCircle(
            pNode->m_ObjectDynamicList[iObj]->m_Circle,
            pSrcObject->m_Circle))
        {
            list.push_back(pNode->m_ObjectDynamicList[iObj]);
        }*/
    }
    if (pNode->m_pChild[0] != nullptr)
    {
        for (int iChild = 0; iChild < 4; iChild++)
        {
            if (KCollision::RectToRect(
                pNode->m_pChild[iChild]->m_rt,
                pSrcObject->m_rt))
            {
                GetCollisitionObject(pNode->m_pChild[iChild], 
                    pSrcObject, list);
            }
        }
    }
}

bool   KQuadtree::IsNodeInObject(KNode* pNode, KBaseObject* pObj)
{
    bool bIn = KCollision::RectToInRect(pNode->m_rt,   pObj->m_rt);
    return bIn;
}

KQuadtree::KQuadtree()
{}
KQuadtree::~KQuadtree()
{}