#include "KMapObject.h"

bool KMapObject::Frame()
{
    m_VertexList[0].t = {0.0f,0.0f };
    m_VertexList[1].t = {1.0f, 0.0f };
    m_VertexList[2].t = {0.0f,1.0f };
    m_VertexList[3].t = {1.0f,1.0f };
    //gpu update cpu에서 명령하지만 gpu에서 업데이트하게 해준다
    //위치이동

    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);

    return true;
}
