#include "Sample.h"
//#include"KGameCore.cpp"
KSpacePartition* GetInstance(int iType)
{
    if (iType == K_OCTREE) return new KOctree;
    if (iType == K_QUADTREE) return new KQuadtree;
    return nullptr;
}

bool	Sample::Init()
{
    m_object.SetDevice(m_pd3dDevice,m_pImmediateContext);
    m_object.Create();

#ifdef OCTREE
    game3D.m_pWorldSP = GetInstance(K_OCTREE);
    game3D.m_pPlayer = new KGamePlayer;
    game3D.m_pPlayer->SetPosition(KVector(50, 50, 50), KVector(50, 50, 50));
    game3D.m_pWorldSP->Create(KVector(0, 0, 0), KVector(100, 100, 0));
    game3D.Run();
#else
    game2D.m_pd3dDevice = m_pd3dDevice;
    game2D.m_pImmediateContext = m_pImmediateContext;
    game2D.m_pWorldSP = GetInstance(K_QUADTREE);
    game2D.m_pPlayer = new KGamePlayer2D;
    game2D.m_pPlayer->GetImp()->SetDevice(m_pd3dDevice, m_pImmediateContext);
    game2D.m_pPlayer->GetImp()->Create();
    game2D.m_pPlayer->GetImp()->Init();
    game2D.m_pPlayer->SetPosition(KVector2D(75, 95), KVector2D(50, 50));
    game2D.m_pWorldSP->Create(KVector2D(0, 0), KVector2D(100, 100));
    game2D.Init();
    //game2D.Run();
#endif

    return true;
}
bool		Sample::Frame()
{
    m_object.Frame();
   // game2D.m_pPlayer->Frame(m_fElapseTimer,m_fGameTimer);
    game2D.Frame(m_fElapseTimer, m_fGameTimer);
    return true;
}
bool		Sample::Render()
{
   // m_object.Render();
   // game2D.m_pPlayer->Render();
    game2D.Render();
    return true;
}
bool		Sample::Release()
{
    //m_object.Release();
    return true;
}



GAME_RUN(DrawOctree, 1024, 768)