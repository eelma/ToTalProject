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
    m_VertexList[0].t = { 0.0f,0.0f };
    m_VertexList[1].t = { 0.5f,0.0f };
    m_VertexList[2].t = { 0.0f,1.0f };
    m_VertexList[3].t = { 0.5f,1.0f };


    //gpu update cpu���� ��������� gpu���� ������Ʈ�ϰ� ���ش�
    //��ġ�̵� ��ũ���۾� ���� �Ѹǿ��� �ʿ���� ��?��?��?
    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, NULL,
        &m_VertexList.at(0), 0, 0);
    //����Ʈ ������ �ι��ϸ� ���� ���ؽ����� ������ �ι� ������
    PostRender();
    m_VertexList[0].t = { 0.5f,0.0f };
    m_VertexList[1].t = { 1.0f,0.0f };
    m_VertexList[2].t = { 0.5f,1.0f };
    m_VertexList[3].t = { 1.0f,1.0f };


    //gpu update cpu���� ��������� gpu���� ������Ʈ�ϰ� ���ش�
    //��ġ�̵� ��ũ���۾� ���� �Ѹǿ��� �ʿ���� ��?��?��?
    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, NULL,
        &m_VertexList.at(0), 0, 0);
    PostRender();

    return true;
}
