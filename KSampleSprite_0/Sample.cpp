#include "Sample.h"
#include"KTextureManager.h"
void KUser2D::UpdateVertexBuffer()
{
    m_VertexList[0].p = { m_vDrawPos.x, m_vDrawPos.y,  0.0f };
    m_VertexList[0].t = { m_rtUV.x1,m_rtUV.y1 };

    m_VertexList[1].p = { m_vDrawPos.x+m_vDrawSize.x, m_vDrawPos.y,  0.0f };
    m_VertexList[1].t = { m_rtUV.x1+m_rtUV.w,m_rtUV.y1 };

    m_VertexList[2].p = { m_vDrawPos.x, m_vDrawPos.y-m_vDrawSize.y, 0.0f };
    m_VertexList[2].t = { m_rtUV.x1,m_rtUV.y1+m_rtUV.h };

    m_VertexList[3].p = m_VertexList[2].p;
    m_VertexList[3].t = m_VertexList[2].t;

    m_VertexList[4].p = m_VertexList[1].p;
    m_VertexList[4].t = m_VertexList[1].t;

    m_VertexList[5].p = { m_vDrawPos.x+m_vDrawSize.x, m_vDrawPos.y - m_vDrawSize.y, 0.0f };
    m_VertexList[5].t = { m_rtUV.x1+m_rtUV.w,m_rtUV.y1 + m_rtUV.h };

    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, NULL, NULL,&m_VertexList.at(0), 0, 0);
}
void KUser2D::SetRect(KRect rt)
{
    m_rtInit = rt;
    m_pkImageSize.x = m_pTexture->m_Desc.Width;
    m_pkImageSize.y = m_pTexture->m_Desc.Height;
    //image w,h
    //사실상 정점에 들어가는 uv값
    m_rtUV.x1 = rt.x1 / m_pkImageSize.x;//u
    //1
    m_rtUV.y1 = rt.y1 / m_pkImageSize.y;//v
    //40
    m_rtUV.w = rt.w / m_pkImageSize.x;
    //60
    m_rtUV.h = rt.h/ m_pkImageSize.y;
    
}
//vPos(화면 좌표)를 ndc 좌표로 변경(컨버팅)해야한다
//화면 좌표로 세팅하고 내부적으로 ndc로 랜더링을한다
//ndc좌표를 만들어주는 기능이 필요하다
void KUser2D::SetPosition(KVector2D vPos)
{
    m_vPos = vPos;
    //0~800 -> 0~1-> -1~+1
    //ndc좌표
    m_vDrawPos.x = (vPos.x / g_rtClient.right)*2.0f-1.0f;
    m_vDrawPos.y = -((vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
    m_vDrawSize.x = (m_rtInit.w / g_rtClient.right)*2;
    m_vDrawSize.y = ((m_rtInit.h / g_rtClient.bottom))*2;
    UpdateVertexBuffer();
}

void KNpc2D::UpdateVertexBuffer()
{
    m_VertexList[0].p = { m_vDrawPos.x, m_vDrawPos.y,  0.0f };
    m_VertexList[0].t = { m_rtUV.x1,m_rtUV.y1 };

    m_VertexList[1].p = { m_vDrawPos.x + m_vDrawSize.x, m_vDrawPos.y,  0.0f };
    m_VertexList[1].t = { m_rtUV.x1 + m_rtUV.w,m_rtUV.y1 };

    m_VertexList[2].p = { m_vDrawPos.x, m_vDrawPos.y - m_vDrawSize.y, 0.0f };
    m_VertexList[2].t = { m_rtUV.x1,m_rtUV.y1 + m_rtUV.h };

    m_VertexList[3].p = m_VertexList[2].p;
    m_VertexList[3].t = m_VertexList[2].t;

    m_VertexList[4].p = m_VertexList[1].p;
    m_VertexList[4].t = m_VertexList[1].t;

    m_VertexList[5].p = { m_vDrawPos.x + m_vDrawSize.x, m_vDrawPos.y - m_vDrawSize.y, 0.0f };
    m_VertexList[5].t = { m_rtUV.x1 + m_rtUV.w,m_rtUV.y1 + m_rtUV.h };

    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);
}
void KNpc2D::SetRect(KRect rt)
{
    m_rtInit = rt;
    m_pkImageSize.x = m_pTexture->m_Desc.Width;
    m_pkImageSize.y = m_pTexture->m_Desc.Height;
    //image w,h
    //사실상 정점에 들어가는 uv값
    m_rtUV.x1 = rt.x1 / m_pkImageSize.x;//u
    //1
    m_rtUV.y1 = rt.y1 / m_pkImageSize.y;//v
    //40
    m_rtUV.w = rt.w / m_pkImageSize.x;
    //60
    m_rtUV.h = rt.h / m_pkImageSize.y;

}
//vPos(화면 좌표)를 ndc 좌표로 변경(컨버팅)해야한다
//화면 좌표로 세팅하고 내부적으로 ndc로 랜더링을한다
//ndc좌표를 만들어주는 기능이 필요하다
void KNpc2D::SetPosition(KVector2D vPos)
{
    m_vPos = vPos;
    //0~800 -> 0~1-> -1~+1
    //ndc좌표
    m_vDrawPos.x = (vPos.x / g_rtClient.right) * 2.0f - 1.0f;
    m_vDrawPos.y = -((vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
    m_vDrawSize.x = (m_rtInit.w / g_rtClient.right) * 2;
    m_vDrawSize.y = ((m_rtInit.h / g_rtClient.bottom)) * 2;
    UpdateVertexBuffer();
}
bool KNpc2D::Frame()
{
   
    return true;
}

bool KUser2D::Frame()
{
    KVector2D vPos = m_vPos;
    if (I_Input.GetKey('W'))
    {
        vPos.y +=-1.0f* g_fSecondPerFrame * 100.0f;
    }
    if (I_Input.GetKey('S'))
    {
        vPos.y += 1.0f * g_fSecondPerFrame * 100.0f;
    }
    if (I_Input.GetKey('A'))
    {
        vPos.x += -1.0f * g_fSecondPerFrame * 100.0f;
    }
    if (I_Input.GetKey('D'))
    {
        vPos.x += 1.0f * g_fSecondPerFrame * 100.0f;
    }
    SetPosition(vPos);
    return true;
}

bool	Sample::Init()
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
        L"../../data/shader/DefaultShape.txt");
      if (i % 2 == 0)
      {
          npc->SetRect({ 46,62,68,79 });
      }
      else
      {
          npc->SetRect({ 115,62,37,35 });
      }
    npc->SetPosition({i*100.0f,100.0f });
    m_pNpcList.push_back(npc);
    }

    //user character
    //{90,1,40,60} player 이미지 영역,{400,300}화면 스크린 좌표 버텍스 버퍼가 만들어져야한다
    //-1~+1에 대한 결과가 만들어진다
    //create 하면 -1~1의 버텍스 버퍼가 만들어진다 그 다음에 오브젝트에 푸쉬백
    m_pUser = new KUser2D;
    m_pUser->Create(m_pd3dDevice, m_pImmediateContext,
        L"../../data/bitmap1.bmp",
        L"DefaultShapeMask.txt");
    m_pUser->SetMask(pMaskTex);
    m_pUser->SetRect({ 91,2,40,59 });
    m_pUser->SetPosition({ g_rtClient.right / 2.0f,g_rtClient.bottom - 100.0f });


    
    return true;
}
bool		Sample::Frame()
{
    m_pMap->Frame();
    for (auto obj : m_pNpcList)
    {
        obj->Frame();
    }
    m_pUser->Frame();
    return true;
}
bool		Sample::Render()
{
    m_pMap->Render();
    for (auto obj : m_pNpcList)
    {
        obj->Render();
        
    }
    m_pUser->PreRender();
    //1번 레지스터에 마스크 이미지를 넘길 수 있다
    m_pImmediateContext->PSSetShaderResources(1, 1, &m_pUser->m_pMaskTex->m_pTextureSRV);
    m_pUser->PostRender();
    return true;
}
bool		Sample::Release()
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
