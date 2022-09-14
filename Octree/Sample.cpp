#include "KGameCore.cpp"
KSpacePartition* GetInstance(int iType)
{
    if (iType == K_OCTREE) return new KOctree;
    if (iType == K_QUADTREE) return new KQuadtree;
    return nullptr;
}
int main()
{        
#ifdef OCTREE
    KGameCore<KObject>game;
    game.m_pWorldSP = GetInstance(K_OCTREE);
    game.m_pPlayer = new KGamePlayer;
    game.m_pPlayer->SetPosition(KVector(50,50,50), KVector(50,50,50));
    game.m_pWorldSP->Create(KVector(0,0,0), KVector(100,100,0));
    game.Run();
#else
    KGameCore<KObject2D>game;
    game.m_pWorldSP = GetInstance(K_QUADTREE);
    game.m_pPlayer = new KGamePlayer2D;
    game.m_pPlayer->SetPosition(KVector2D(50, 50), KVector2D(50, 50));
    game.m_pWorldSP->Create(KVector2D(0, 0), KVector2D(100, 100));
    game.Run();
#endif
    
    std::cout << "Game Ending!\n";
}
