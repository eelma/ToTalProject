#pragma once
#include <windows.h>
#include <map>
#include <queue>
#include <iostream>
#include "KCollision.h"
#include "KObject.h"
class KNode 
{
public:
    KBox    m_Box;
    int     m_iDepth;
    KRect   m_rt;
    std::vector<KBaseObject*>   m_ObjectStaticList;
    std::vector<KBaseObject*>   m_ObjectDynamicList;
    std::vector<KNode*>         m_pChild;    
    KNode*                      m_pParent;
public:
    KNode();
    KNode(KNode* pParent,KVector vPos,KVector vSize);
    KNode(KNode* pParent, KVector2D p, KVector2D s);
    ~KNode();
};
