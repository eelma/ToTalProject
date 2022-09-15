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
    ID3D11Device*          m_pd3dDevice = nullptr;// 디바이스 객체
    ID3D11DeviceContext*   m_pImmediateContext = nullptr;
public:
    KSpacePartition*        m_pWorldSP;
    std::map<int, KBaseObject*> m_npcList;
    std::map<int, KBaseObject*> m_AllObjectList;
    std::vector<KBaseObject*>   m_DrawList;
public:
    bool    Init();     // 초기화	
    bool    Frame(float fDeltaTime, float fGameTime);    // 실시간 계산
    bool    Render();   // 화면에 드로우
    bool    Release();  // 소멸하자
    bool	Run();      // 실행하자
};

