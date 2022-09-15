#include "KEnemy.h"
KEnemy2D::KEnemy2D()
{
    m_fFriction = 1.0f;
}
KEnemy2D::KEnemy2D(std::string name) : KObject2D(name)
{
    m_fFriction = 1.0f;
}
bool   KEnemy2D::Render()
{
    KBaseObject::Render();
    std::cout << m_csName << ","
        << m_rt.x1 << ","
        << m_rt.y1 << std::endl;
    return true;
};
KEnemy::KEnemy()
{

}
KEnemy::KEnemy(std::string name) : KObject(name)
{

}
bool   KEnemy::Render() {
    std::cout << m_csName << ","
        << m_Box.vMin.x << ","
        << m_Box.vMin.y << ","
        << m_Box.vMin.z << std::endl;
    return true;
};

// ������ ���Ģ
// 1)������ ��Ģ:���¸� ���� �ҷ��� Ư��
// 2)���ӵ��� ��Ģ: ��(Force)�� ����Ͽ� ���� �������� �����δ�.
//   ���ӵ� : �ð��� ���� �ӵ��� �������� ��ȭ��
// 3)�ۿ�, ���ۿ� ��Ģ
//   ��(�ۿ�)�� ���� ��ü�� �ݴ�������� ��(���ۿ�)�� ��������. 
bool KEnemy::Frame(float fDeltaTime, float fGameTime)
{
    KVector vPos = m_Box.vMin;
    KVector vSize = m_Box.vSize;
    //������ ������ ������ &  �ð��� ����ȭ
    m_vVelocity = m_vDirection* m_fSpeed* fDeltaTime;    
    vPos = vPos + m_vVelocity;
    m_fFriction = (fDeltaTime * m_fSpeed * 0.1f);
    m_fSpeed -= m_fFriction;
    if (0 >= m_fSpeed)
    {
        m_fSpeed = 10+rand() % 10;
    }

    if (vPos.x > 100.0f)
    {
        vPos.x = 100.0f;
        m_vDirection.x *= -1.0f;
    }
    if (vPos.x < 0.0f)
    {
        vPos.x = 0.0f;
        m_vDirection.x *= -1.0f;
    }
    if (vPos.y > 100.0f)
    {
        vPos.y = 100.0f;
        m_vDirection.y *= -1.0f;
    }
    if (vPos.y < 0.0f)
    {
        vPos.y = 0.0f;
        m_vDirection.y *= -1.0f;
    }
    if (vPos.z > 100.0f)
    {
        vPos.z = 100.0f;
        m_vDirection.z *= -1.0f;
    }
    if (vPos.z < 0.0f)
    {
        vPos.z = 0.0f;
        m_vDirection.z *= -1.0f;
    }
    SetPosition(vPos, vSize);
    return true;
}
bool KEnemy2D::Frame(float fDeltaTime, float fGameTime)
{
    KVector2D vPos(m_rt.x1, m_rt.y1);
    KVector2D vSize(m_rt.w, m_rt.h);
    //������ ������ ������ &  �ð��� ����ȭ
    m_vVelocity2D = m_vDirection2D * m_fSpeed * fDeltaTime;
    vPos = vPos + m_vVelocity2D;
    //m_fFriction = (fDeltaTime * m_fSpeed * 0.1f);
    m_fSpeed -= m_fFriction*fDeltaTime;
    if (0 >= m_fSpeed)
    {
        m_fSpeed = rand() % 10;
    }

    if (vPos.x > 100.0f)
    {
        vPos.x = 100.0f;
        m_vDirection2D.x *= -1.0f;
    }
    if (vPos.x < 0.0f)
    {
        vPos.x = 0.0f;
        m_vDirection2D.x *= -1.0f;
    }
    if (vPos.y > 100.0f)
    {
        vPos.y = 100.0f;
        m_vDirection2D.y *= -1.0f;
    }
    if (vPos.y < 0.0f)
    {
        vPos.y = 0.0f;
        m_vDirection2D.y *= -1.0f;
    }
    SetPosition(vPos, vSize);
    return true;
}

void   KEnemy2D::SetPosition(KVector2D p, KVector2D s)
{
    float x1 = ((p.x / 100.0f) * 2 - 1.0f);
    float y1 = ((p.y / 100.0f) * 2 - 1.0f);
    float w1 = ((s.x / 100.0f) * 2);
    float h1 = ((s.y / 100.0f) * 2);

    m_VertexList[0].p = { x1,y1,0.0f };
    m_VertexList[1].p = { x1 + w1,y1,0.0f };
    m_VertexList[2].p = { x1,y1 - h1,0.0f };
    m_VertexList[3].p = m_VertexList[2].p;
    m_VertexList[4].p = m_VertexList[1].p;
    m_VertexList[5].p = { x1 + w1,y1 - h1,0.0f };

    m_VertexList[0].c = {0,0,1.0f,1.0f};
    m_VertexList[1].c = {0,0,1.0f,1.0f};
    m_VertexList[2].c = {0,0,1.0f,1.0f};
    m_VertexList[3].c = {0,0,1.0f,1.0f};
    m_VertexList[4].c = {0,0,1.0f,1.0f};
    m_VertexList[5].c = {0,0,1.0f,1.0f};

    m_rt.Set(p.x, p.y, s.x, s.y);
    SetCircle(m_rt.cx, m_rt.cy, m_rt.w, m_rt.h);

}