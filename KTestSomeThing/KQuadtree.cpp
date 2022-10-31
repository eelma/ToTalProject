#include "KQuadtree.h"
#include "KCollision.h"
bool KQuadtree::Create(KCamera* pMainCamera, KMap* pMap, int iMaxDepth)
{
    m_pCamera = pMainCamera;
    m_pMap = pMap;
    m_iMaxDepth = iMaxDepth;
    m_pRootNode = new KNode(nullptr,m_pMap,
        0,
        pMap->m_dwNumRows - 1,
        pMap->m_dwNumRows * (pMap->m_dwNumColumns - 1),
        pMap->m_dwNumRows * pMap->m_dwNumColumns - 1,
        pMap->m_dwNumColumns, pMap->m_dwNumRows);
    BuildTree(m_pRootNode);
    return true;
}
KNode* KQuadtree::FindNode(KNode* pNode, KObject3D* pObj)
{
    for (int i = 0; i < 4; i++)
    {
        if (pNode->m_pChild[i] != nullptr)
        {
            /*if (TCollision::RectToInRect(pNode->m_pChild[i]->m_rt, pObj->m_rt))
            {
                pNode = FindNode(pNode->m_pChild[i], pObj);
                break;
            }*/
        }
    }
    return pNode;
}
bool KQuadtree::AddObject(KObject3D* pObj)
{
    KNode* pFindNode = FindNode(m_pRootNode, pObj);
    if (pFindNode != nullptr)
    {
        pFindNode->m_pDynamicObjectlist.push_back(pObj);
        return true;
    }
    return false;
}
void KQuadtree::Reset(KNode* pNode)
{
    if (pNode == nullptr) return;
    pNode->m_pDynamicObjectlist.clear();
    Reset(pNode->m_pChild[0]);
    Reset(pNode->m_pChild[1]);
    Reset(pNode->m_pChild[2]);
    Reset(pNode->m_pChild[3]);
}

void KQuadtree::BuildTree(KNode* pNode)
{
    if (pNode == nullptr) return;
    if (IsSubDivide(pNode) == false)
    {
        pNode->m_bLeaf = true;
        m_pLeafNodeList.push_back(pNode);
        return;
    }
    pNode->CreateChildNode(pNode,m_pMap,
        m_pMap->m_dwNumRows, m_pMap->m_dwNumColumns);

    BuildTree(pNode->m_pChild[0]);
    BuildTree(pNode->m_pChild[1]);
    BuildTree(pNode->m_pChild[2]);
    BuildTree(pNode->m_pChild[3]);
}

bool KQuadtree::IsSubDivide(KNode* pNode)
{
    if ((pNode->m_Corner[1] - pNode->m_Corner[0]) == 1) return false;
    if (pNode->m_iDepth < m_iMaxDepth) return true;
    return false;
}
bool KQuadtree::Frame()
{
    m_pDrawLeafNodeList.clear();
    VisibleNode(m_pRootNode);
    /*
     for (auto node : m_pLeafNodeList)
     {
         if (m_pCamera->m_vFrustum.ClassifyTBox(node->m_kBox))
         {
             m_pDrawLeafNodeList.push_back(node);
         }
     }*/
    return true;
}
bool KQuadtree::Render()
{
    for (auto node : m_pDrawLeafNodeList)
    {
        m_pMap->PreRender();
        m_pMap->m_pImmediateContext->IASetIndexBuffer(
            node->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        m_pMap->m_pImmediateContext->DrawIndexed(node->m_dwFace * 3, 0, 0);
    }
    return true;
}
KNode* KQuadtree::VisibleNode(KNode* pNode)
{
    K_POSITION dwRet = m_pCamera->m_vFrustum.ClassifyKBOX(pNode->m_kBox);
    if (P_FRONT == dwRet)
    {
        m_pDrawLeafNodeList.push_back(pNode);
        return pNode;
    }
    if (P_SPANNING == dwRet)
    {
        if (pNode->m_bLeaf)
        {
            m_pDrawLeafNodeList.push_back(pNode);

        }
        else
        {
            for (int iNode = 0; iNode < 4; iNode++)
            {
                VisibleNode(pNode->m_pChild[iNode]);
            }
        }


    }
    return nullptr;
}
KQuadtree::~KQuadtree()
{
    if (m_pRootNode)
    {
        delete m_pRootNode;
        m_pRootNode = nullptr;
    }
}