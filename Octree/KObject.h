#pragma once
#include "KCollision.h"
#include <string>
class KBaseObject
{
public:
    std::string  m_csName;
    float       m_fFriction;
    float       m_fMass;
    float       m_fSpeed;
public:
    KVector    m_vDirection;
    KBox       m_Box;
    KSphere    m_Sphere;
    KVector    m_vAcceleration;
    KVector    m_vVelocity;
    KVector    m_vForces;
public:
    KVector2D   m_vDirection2D;
    KRect       m_rt;
    KCircle     m_Circle;
    KVector2D   m_vAcceleration2D;
    KVector2D   m_vVelocity2D;
    KVector2D   m_vForces2D;    
public:
    virtual void   Init() {};
    virtual void   Frame(float fDeltaTime, float fGameTime) {};
    virtual void   Render() {};
};
class KObject2D : public KBaseObject
{
public:
    void   SetCircle(float x, float y, float w, float h);
    void   SetPosition(float x, float y, float w, float h);
    void   SetCircle(KVector2D p, KVector2D s);
    void   SetPosition(KVector2D p, KVector2D s);
public:
    virtual void   Init() override;
    virtual void   Frame(float fDeltaTime, float fGameTime)override;
    virtual void   Render() override;
    virtual void   AddForces(KVector2D f);
public:
    KObject2D();
    KObject2D(std::string name);
};
class KObject : public KBaseObject
{
public:
    void   SetSphere(KVector vCenter, float radius);
    void   SetSphere(KBox box);
    void   SetPosition(KVector p, KVector s);
public:
    virtual void   Init() override;
    virtual void   Frame(float fDeltaTime, float fGameTime)override;
    virtual void   Render() override;
public:
    virtual void   AddForces(KVector f);
public:
    KObject();
    KObject(std::string name);
};