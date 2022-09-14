#include "KNode.h"
KNode::KNode(KNode* pParent, KVector2D p, KVector2D s)
{
    m_rt.Set(p.x, p.y, s.x, s.y);
    m_iDepth = 0;
    m_pParent = nullptr;
    if (pParent != nullptr)
    {
        m_pParent = pParent;
        m_iDepth = pParent->m_iDepth + 1;
    }    
}
KNode::KNode()
{

}
KNode::KNode(KNode* pParent, KVector vPos,KVector vSize)
{
    m_Box.Set(vPos, vSize);
    m_iDepth = 0;
    m_pParent = nullptr;
    if (pParent != nullptr)
    {
        m_pParent = pParent;
        m_iDepth = pParent->m_iDepth + 1;
    }
}
KNode::~KNode()
{
    for (int iChild = 0; iChild < m_pChild.size(); iChild++)
    {
        delete m_pChild[iChild];
    }
}