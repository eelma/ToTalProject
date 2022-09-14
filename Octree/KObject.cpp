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
    m_rt.Set(x, y, w, h);
    SetCircle(m_rt.cx, m_rt.cy, m_rt.w, m_rt.h);
}

void   KObject2D::Frame(float fDeltaTime, float fGameTime) {};
void   KObject2D::Render() {
    std::cout << m_csName << ","
        << m_rt.x1 << ","
        << m_rt.y1 << std::endl;
};
void   KObject2D::Init()
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
}
KObject2D::KObject2D()
{
    Init();
}
KObject2D::KObject2D(std::string name)
{
    Init();
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

void   KObject::Frame(float fDeltaTime, float fGameTime) {};
void   KObject::Render() {
    std::cout << m_csName << ","
        << m_Box.vMin.x << ","
        << m_Box.vMin.y << ","
        << m_Box.vMin.z << std::endl;
};
void   KObject::Init()
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