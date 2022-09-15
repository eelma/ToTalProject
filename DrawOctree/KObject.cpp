#include "KObject.h"

void   KObject2D::AddForces(KVector2D f)
{
    m_vForces2D += f;
}
void   KObject2D::SetCircle(KVector2D c, KVector2D s)
{
    m_Circle.cx = c.x;
    m_Circle.cy = c.y;
    float x1 = s.x / 2.0f;
    float y1 = s.y / 2.0f;
    m_Circle.fRadius = sqrt(x1 * x1 + y1 * y1);
}
void   KObject2D::SetPosition(KVector2D p, KVector2D s)
{
    float x1 = ((p.x/100.0f) * 2 - 1.0f);
    float y1 = ((p.y/100.0f) * 2 - 1.0f);
    float w1 = ((s.x/100.0f) * 2);
    float h1 = ((s.y/100.0f) * 2);

    m_VertexList[0].p = { x1,y1,0.0f };
    m_VertexList[1].p = { x1 + w1,y1,0.0f };
    m_VertexList[2].p = { x1,y1 - h1,0.0f };
    m_VertexList[3].p = m_VertexList[2].p;
    m_VertexList[4].p = m_VertexList[1].p;
    m_VertexList[5].p = { x1+w1,y1 - h1,0.0f };

    m_rt.Set(p.x, p.y, s.x, s.y);
    SetCircle(m_rt.cx, m_rt.cy, m_rt.w, m_rt.h);

}
void   KObject2D::SetCircle(float x, float y, float w, float h)
{
    m_Circle.cx = x;
    m_Circle.cy = y;
    float x1 = w / 2.0f;
    float y1 = h / 2.0f;
    m_Circle.fRadius = sqrt(x1 * x1 + y1 * y1);
}
void   KObject2D::SetPosition(float x, float y, float w, float h)
{
    // convert( -1 ~ +1 -> 0 ~ 1) x * 0.5f + 0.5f
    // screen(0 ~ 100) -> ndc(-1 ~ +1)
    // 1) 0~ 100 -> 0~1 
    //  0 -> 0;  x/=100.0f
    // 50 -> 0.5f;
    // 100 -> 1
    // 
    // 2) 0~ 1 -> -1~ 1 x * 2 -1.0f
    // 0 -> -1;
    // 50 -> 0;
    // 100 -> 1
    float x1 = (x * 2 - 1.0f) / 100.f;
    float y1 = (y * 2 - 1.0f) / 100.f;
    float w1 = (w * 2 - 1.0f) / 100.f;
    float h1 = (h * 2 - 1.0f) / 100.f;

    m_VertexList[0].p = { x1,y1,0.0f };
    m_VertexList[1].p = { x1+w1,y1,0.0f };
    m_VertexList[2].p = { x1,y1-h1,0.0f };
    m_VertexList[3].p = m_VertexList[2].p;
    m_VertexList[4].p = m_VertexList[1].p;
    m_VertexList[5].p = { x1,y1 - h1,0.0f };


    m_rt.Set(x, y, w, h);
    SetCircle(m_rt.cx, m_rt.cy, m_rt.w, m_rt.h);
}

bool   KObject2D::Frame(float fDeltaTime, float fGameTime) {
    KBaseObject::Frame();
    return true; };
bool   KObject2D::Render() {
    KBaseObject::Render();
    std::cout << m_csName << ","
        << m_rt.x1 << ","
        << m_rt.y1 << std::endl;
    return true;
};
bool   KObject2D::Init()
{
    m_rt.Set(20 + (rand() % 80),
        20 + (rand() % 80),
        5.0f + (rand() % 5),
        5.0f + (rand() % 5));
    SetCircle(m_rt.cx, m_rt.cy, m_rt.w, m_rt.h);
    m_vDirection2D.x = cos(rand());
    m_vDirection2D.y = sin(rand());
    m_vDirection2D.Normalized();
    m_fFriction = 0.0f;
    m_fMass = 100.0f;
    m_fSpeed = 10.0f;

    SetPosition(KVector2D(m_rt.x1, m_rt.y1), KVector2D(m_rt.w, m_rt.h));
    return true;
}
KObject2D::KObject2D()
{
   // Init();
}
KObject2D::KObject2D(std::string name)
{
   // Init();
    m_csName = name;
}
////////////////////////////////////////////////////////
void        KObject::AddForces(KVector f)
{
    m_vForces += f;
}
void   KObject::SetSphere(KVector vCenter, float radius)
{
    m_Sphere.vCenter = vCenter;
    m_Sphere.fRadius = radius;
}
void   KObject::SetSphere(KBox box)
{
    m_Sphere.vCenter = box.vCenter;    
    // v0  -vC-  v1
    m_Sphere.fRadius = (box.vSize*0.5f).Length();    
}
void   KObject::SetPosition(KVector vPos, KVector vSize)
{
    m_Box.Set(vPos, vSize);
    SetSphere(m_Box);
}

bool   KObject::Frame(float fDeltaTime, float fGameTime) { return true; };
bool   KObject::Render() {
    std::cout << m_csName << ","
        << m_Box.vMin.x << ","
        << m_Box.vMin.y << ","
        << m_Box.vMin.z << std::endl;
    return true;
};
bool   KObject::Init()
{
    KVector vPos, vSize;
    vPos.x = 20 + (rand() % 80);
    vPos.y = 20 + (rand() % 80);
    vPos.z = 20 + (rand() % 80);
    vSize.x = 5.0f + (rand() % 5);
    vSize.y = 5.0f + (rand() % 5);
    vSize.z = 5.0f + (rand() % 5);
    m_Box.Set(vPos, vSize);
    SetSphere(m_Box);
    m_vDirection.x = cos(rand());
    m_vDirection.y = sin(rand());
    m_vDirection.z = 1.0f - cos(rand());
    m_vDirection.Normalized();
    m_fFriction = 0.0f;
    m_fMass = 100.0f;
    m_fSpeed = 10.0f;

    
    return true;
}
KObject::KObject()
{
    Init();
}
KObject::KObject(std::string name)
{
    Init();
    m_csName = name;
}