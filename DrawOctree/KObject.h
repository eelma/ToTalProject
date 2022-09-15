#pragma once
#include"KBaseObject.h"
#include <string>

class KObject2D : public KBaseObject
{
public:
    virtual void   SetCircle(float x, float y, float w, float h);
    virtual void   SetPosition(float x, float y, float w, float h);
    virtual void   SetCircle(KVector2D p, KVector2D s);
    virtual void   SetPosition(KVector2D p, KVector2D s);
public:
    virtual bool   Init() override;
    virtual bool   Frame(float fDeltaTime, float fGameTime)override;
    virtual bool   Render() override;
    virtual void   AddForces(KVector2D f);
public:
    KObject2D();
    KObject2D(std::string name);
};
class KObject : public KBaseObject
{
public:
    virtual void   SetSphere(KVector vCenter, float radius);
    virtual void   SetSphere(KBox box);
    virtual void   SetPosition(KVector p, KVector s);
public:
    virtual bool   Init() override;
    virtual bool   Frame(float fDeltaTime, float fGameTime)override;
    virtual bool   Render() override;
public:
    virtual void   AddForces(KVector f);
public:
    KObject();
    KObject(std::string name);
};