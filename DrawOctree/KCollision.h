#pragma once
#include "KVector.h"
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
        x2 = x + w;
        y2 = y + h;
        cx = (x + x2) / 2.0f;
        cy = (y + y2) / 2.0f;
    }
};

struct KSphere
{
    KVector vCenter;
    float fRadius;
    KSphere() {};
    KSphere(KVector vC,  float r) {
        vCenter = vC;
        fRadius = r;
    };
};
struct Box
{
    KVector vMin;
    KVector vSize;
};
struct KBox : Box
{
    KVector vMax;
    KVector vCenter;
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
    KBox(KVector vPos,KVector vSize) 
    {
        Set(vPos, vSize);
    }
    void  Set(KVector vPos,KVector vSize)
    {
        vMin = vPos;
        this->vSize = vSize;
        vMax = vMin + vSize;
        vCenter = (vMin + vMax) / 2.0f;
    }
};

class KCollision
{
public:
    static KCollisionType   RectToRect(KRect& a, KRect& b);
    static bool             RectToInRect(KRect& a, KRect& b);
    static bool             CircleToCircle(KCircle& a, KCircle& b);
public:
    static KCollisionType   BoxToBox(KBox& a, KBox& b);
    static bool             BoxToInBox(KBox& a, KBox& b);
    static bool             SphereToSphere(KSphere& a, KSphere& b);
};
