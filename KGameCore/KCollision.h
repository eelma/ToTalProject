#pragma once
#include"KVector.h"
#include"KMatrix.h"
#include <vector>
#include <queue>

enum KCollisionType
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};

struct KCircle
{
    float cx;
    float cy;
    float fRadius;
    KCircle() {};
    KCircle(float x, float y, float r) {
        cx = x;
        cy = y;
        fRadius = r;
    };
};
struct Rect
{
    float  x1;
    float  y1;
    float  w;
    float  h;
};

struct KRect : Rect
{
    float  x2;//x+w
    float  y2;//y+h
    float  cx;
    float  cy;
    bool   operator == (KRect& dest)
    {
        if (fabs(x1 - dest.x1) < T_Epsilon)
        {
            if (fabs(y1 - dest.y1) < T_Epsilon)
            {
                if (fabs(w - dest.w) < T_Epsilon)
                {
                    if (fabs(h - dest.h) < T_Epsilon)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    KRect() {}
    KRect(float x, float y, float z, float w) {
        Set(x, y, z, w);
    }
    void  Set(float x, float y, float z, float w)
    {
        this->x1 = x;
        this->y1 = y;
        this->w = z;
        this->h = w;
        x2 = this->x1 + this->w;
        y2 = this->y1 + this->h;
        cx = (this->x1 + x2) / 2.0f;
        cy = (this->y1 + y2) / 2.0f;
    }
};

struct KSphere
{
    TVector3 vCenter;
    float fRadius;
    KSphere() {};
    KSphere(TVector3 vC,  float r) {
        vCenter = vC;
        fRadius = r;
    };
};
struct Box
{
    TVector3 vMin;
    TVector3 vSize;
};
struct KBox : Box
{
    TVector3 vMax;
    TVector3 vCenter;
    bool   operator == (KBox& dest)
    {
        if ( vMin == dest.vMin)
        {
            if (vSize == dest.vSize)
            {
               return true;                      
            }          
        }
        return false;
    }
    KBox(){}
    KBox(TVector3 vPos,TVector3 vSize) 
    {
        Set(vPos, vSize);
    }
    void  Set(TVector3 vPos,TVector3 vSize)
    {
        vMin = vPos;
        this->vSize = vSize;
        vMax = vMin + vSize;
        vCenter = (vMin + vMax) / 2.0f;
    }
};
class K_AABB
{
    TVector3 vMin;
    TVector3 vMax;
};
class K_OBB
{
    TVector3 vCenter;
    TVector3 vAxis[3];
    float fDistance[3];
};
struct K_BOX
{
    TVector3 vPos[8];
    //aabb
    TVector3 vMin;
    TVector3 vMax;
    //obb
    TVector3 vCenter;
    TVector3 vAxis[3];
    float fExtent[3];
};

class KCollision
{
public:
    //static KCollisionType   RectToRect(KRect& a, KRect& b, KRect& Intersect);
    static KCollisionType   RectToRect(KRect& a, KRect& b);
    static bool             RectToInRect(KRect& a, KRect& b);
    static bool             CircleToCircle(KCircle& a, KCircle& b);
public:
    static KCollisionType   BoxToBox(KBox& a, KBox& b);
    static bool             BoxToInBox(KBox& a, KBox& b);
    static bool             SphereToSphere(KSphere& a, KSphere& b);
};
