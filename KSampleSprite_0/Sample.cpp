#include "Sample.h"





bool Sample::Init()
{
    KTexture*pMaskTex= I_Tex.Load(L"../../data/bitmap2.bmp");
   
    //map
    m_pMap = new KBaseObject;    
    m_pMap->Create(m_pd3dDevice, m_pImmediateContext,
        L"../../data/KGCABK.bmp",    
        L"../../data/shader/DefaultShape.txt");    

    for(int i=0;i<7;i++)
    {
      KNpc2D * npc = new KNpc2D;
      npc->Create(m_pd3dDevice, m_pImmediateContext,
        L"../../data/bitmap1.bmp",
        L"DefaultShapeMask.txt");
      if (i % 2 == 0)
      {
          npc->SetRect({ 46,62,68,79 });
      }
      else
      {
          npc->SetRect({ 115,62,37,35 });
      }
    npc->SetDirection({randstep(-1.0f, 1.0f),randstep(-1.0f,1.0f)});
    npc->SetPosition({100.0f+i*100.0f,100.0f });
    npc->SetMask(pMaskTex);
    m_pNpcList.push_back(npc);
    }

    //user character
    //{90,1,40,60} player �̹��� ����,{400,300}ȭ�� ��ũ�� ��ǥ ���ؽ� ���۰� ����������Ѵ�
    //-1~+1�� ���� ����� ���������
    //create �ϸ� -1~1�� ���ؽ� ���۰� ��������� �� ������ ������Ʈ�� Ǫ����
    m_pUser = new KUser2D;
    m_pUser->Create(m_pd3dDevice, m_pImmediateContext,
        L"../../data/bitmap1.bmp",
        L"DefaultShapeMask.txt");
    m_pUser->SetMask(pMaskTex);
    m_pUser->m_fSpeed = 300.0f;
    m_pUser->SetRect({ 91,2,40,59 });
    m_pUser->SetPosition({ g_rtClient.right / 2.0f,g_rtClient.bottom - 100.0f });


    
    return true;
}
bool Sample::Frame()
{
    m_pMap->Frame();
    for (auto obj : m_pNpcList)
    {
        obj->Frame();
    }
    m_pUser->Frame();
    return true;
}
bool Sample::Render()
{
    m_pMap->Render();
    for (auto obj : m_pNpcList)
    {
        obj->Render();
        
    }
    m_pUser->PreRender();
    //1�� �������Ϳ� ����ũ �̹����� �ѱ� �� �ִ�
    m_pImmediateContext->PSSetShaderResources(1, 1, &m_pUser->m_pMaskTex->m_pTextureSRV);
    m_pUser->PostRender();
    return true;
}
bool Sample::Release()
{
    m_pMap->Release();
    m_pUser->Release();
    delete m_pUser;
    m_pUser = nullptr;
    for (auto obj : m_pNpcList)
    {
        obj->Release();
        delete obj;
    }
    
    return true;
}


GAME_RUN(KSampleSprite_0, 800, 600)
