#include "KMapObject.h"

bool KMapObject::Frame()
{
    m_VertexList[0].t = { 0.0f,0.0f };
    m_VertexList[1].t = { 1.0f,0.0f };
    m_VertexList[2].t = { 0.0f,1.0f };
    m_VertexList[3].t = { 1.0f,1.0f };
    
    
    //gpu update cpu���� ��������� gpu���� ������Ʈ�ϰ� ���ش�
    //��ġ�̵� ��ũ���۾� ���� �Ѹǿ��� �ʿ���� ��?��?��?
    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, NULL,
        &m_VertexList.at(0), 0, 0);

    return true;
}

bool KMapObject::Render()
{

    PreRender();
    static float fStep = 0.0f;
    UINT iMapWidth = m_pTexture->m_Desc.Width;
    if(I_Input.GetKey('D')>0)
    {
    if (fStep + 0.1f <= 1.0f)
    {
        fStep += g_fSecondPerFrame * 0.1f;
        m_vUser.x = fStep;
    }
    }
    m_VertexList[0].p = { -1.0f, 1.0f, 0.0f };
    m_VertexList[1].p = { 1.0f, 1.0f,  0.0f };
    m_VertexList[2].p = { -1.0f, -1.0f, 0.0f };
    m_VertexList[3].p = { 1.0f, -1.0f, 0.0f };

    m_VertexList[0].t = { 0.0f,0.0f + fStep };
    m_VertexList[1].t = { 0.5f,0.0f + fStep };
    m_VertexList[2].t = { 0.0f,1.0f + fStep };
    m_VertexList[3].t = { 0.5f,1.0f + fStep };


    //gpu update cpu���� ��������� gpu���� ������Ʈ�ϰ� ���ش�
    //��ġ�̵� ��ũ���۾� ���� �Ѹǿ��� �ʿ���� ��?��?��?
    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, NULL,
        &m_VertexList.at(0), 0, 0);
    //����Ʈ ������ �ι��ϸ� ���� ���ؽ����� ������ �ι� ������
    PostRender();

    return true;
}
