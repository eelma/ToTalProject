#include "KMapObject.h"

bool KMapObject::Frame()
{
    m_VertexList[0].t = { 0.0f,0.0f };
    m_VertexList[1].t = { 1.0f,0.0f };
    m_VertexList[2].t = { 0.0f,1.0f };
    m_VertexList[3].t = { 1.0f,1.0f };
    
    static float fStep = 0.0f;
    /*UINT iMapWidth = m_pTexture->m_Desc.Width;
   if(I_Input.GetKey('W')>0)
   {
       m_vUser.y += g_fSecondPerFrame * 10.0f;
   if (iMapWidth>m_vUser.y)
   {
       fStep = m_vUser.y / iMapWidth;
   }
   }*/
    if (fStep + 0.1f <= 1.0f)
    {
        fStep += g_fSecondPerFrame * 0.01f;
    }
    m_VertexList[0].p = { -1.0f, 1.0f, 0.0f };
    m_VertexList[1].p = { 1.0f, 1.0f,  0.0f };
    m_VertexList[2].p = { -1.0f, -1.0f, 0.0f };
    m_VertexList[3].p = { 1.0f, -1.0f, 0.0f };

    m_VertexList[0].t = { 0.0f,0.0f + fStep };
    m_VertexList[1].t = { 1.0f,0.0f + fStep };
    m_VertexList[2].t = { 0.0f,0.1f + fStep };
    m_VertexList[3].t = { 1.0f,0.1f + fStep };


    //gpu update cpu에서 명령하지만 gpu에서 업데이트하게 해준다
    //위치이동 스크롤작업 진행 팩맨에선 필요없다 아?닌?가?
    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, NULL,
        &m_VertexList.at(0), 0, 0);
    //포스트 렌더를 두번하면 같은 버텍스렌더 가지고 두번 랜더링

    //
    ////gpu update cpu에서 명령하지만 gpu에서 업데이트하게 해준다
    ////위치이동 스크롤작업 진행 팩맨에선 필요없다 아?닌?가?
    //m_pImmediateContext->UpdateSubresource(
    //    m_pVertexBuffer, 0, NULL,
    //    &m_VertexList.at(0), 0, 0);

    return true;
}

bool KMapObject::Render()
{
    //스크롤기능
    PreRender();
    
   
    PostRender();

    return true;
}
