#pragma once
#include "KQuadtree.h"
#include "KOctree.h"
#include "KGamePlayer.h"
#include "KEnemy.h"
//#define   OCTREE
template<class T>
class KGameCore
{
public:
    KPlayer<T>*            m_pPlayer;
    ID3D11Device*          m_pd3dDevice = nullptr;// ����̽� ��ü
    ID3D11DeviceContext*   m_pImmediateContext = nullptr;
public:
    KSpacePartition*        m_pWorldSP;
    std::map<int, KBaseObject*> m_npcList;
    std::map<int, KBaseObject*> m_AllObjectList;
    std::vector<KBaseObject*>   m_DrawList;
public:
    bool    Init();     // �ʱ�ȭ	
    bool    Frame(float fDeltaTime, float fGameTime);    // �ǽð� ���
    bool    Render();   // ȭ�鿡 ��ο�
    bool    Release();  // �Ҹ�����
    bool	Run();      // ��������
};

