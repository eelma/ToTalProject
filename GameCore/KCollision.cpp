#include "KCollision.h"
KCollisionType KCollision::RectToRect(KRect& a, KRect& b)
{
    float fMinX;   float fMinY;
    float fMaxX;   float fMaxY;
    fMinX = a.x1 < b.x1 ? a.x1 : b.x1;
    fMinY = a.y1 < b.y1 ? a.y1 : b.y1;
    fMaxX = a.x2 > b.x2 ? a.x2 : b.x2;
    fMaxY = a.y2 > b.y2 ? a.y2 : b.y2;
    if ((a.x1+3)<b.x2)
    {
    if ((a.w + b.w) >= (fMaxX - fMinX))
    {
 
        if ((a.h + b.h) >= (fMaxY - fMinY))
        {
            float x, y, x2, y2;
            KRect Intersect;
            x = a.x1 > b.x1 ? a.x1 : b.y1;
            y = a.y1 > b.y1 ? a.y1 : b.y1;
            x2 = a.x2 < b.x2 ? a.x2 : b.x2;
            y2 = a.y2 < b.y2 ? a.y2 : b.y2;
            Intersect.Set(x, y, x2 - x, y2 - y);
            if (Intersect == a || Intersect == b)
            {
                return KCollisionType::RECT_IN;
            }

            return KCollisionType::RECT_OVERLAP;
        
            }
        }
    }
    return KCollisionType::RECT_OUT;
}

bool    KCollision::RectToInRect(KRect& a, KRect& b)
{
    if (a.x1 <= b.x1)
    {
        if ((a.x1 + a.w) >= b.x1 + b.w)
        {
            if (a.y1 <= b.y1)
            {
                if ((a.y1 + a.h) >= b.y1 + b.h)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool   KCollision::CircleToCircle(KCircle& a, KCircle& b)
{
    float fSumRadius = a.fRadius + b.fRadius;
    float x = a.cx - b.cx;
    float y = a.cy - b.cy;
    float fDistance = sqrt(x * x + y * y);
    if (fDistance <= fSumRadius)
    {
        return true;
    }
    return false;
}

KCollisionType   KCollision::BoxToBox(KBox& a, KBox& b)
{
  
    float fMinX;    float fMaxX;
    float fMinY;    float fMaxY;
    float fMinZ;    float fMaxZ;
    fMinX = a.vMin.x < b.vMin.x ? a.vMin.x : b.vMin.x;
    fMinY = a.vMin.y < b.vMin.y ? a.vMin.y : b.vMin.y;
    fMaxX = a.vMax.x > b.vMax.x ? a.vMax.x : b.vMax.x;
    fMaxY = a.vMax.y > b.vMax.y ? a.vMax.y : b.vMax.y;
    
    fMinZ = a.vMin.z < b.vMin.z ? a.vMin.z : b.vMin.z;
    fMaxZ = a.vMax.z > b.vMax.z ? a.vMax.z : b.vMax.z;

    if ((a.vSize.x + b.vSize.x) >= (fMaxX - fMinX))
    {
        if ((a.vSize.y + b.vSize.y) >= (fMaxY - fMinY))
        {
            if ((a.vSize.z + b.vSize.z) >= (fMaxZ - fMinZ))
            {
                KVector vMin, vMax;
                KBox Intersect;
                vMin.x = a.vMin.x > b.vMin.x ? a.vMin.x : b.vMin.x;
                vMin.y = a.vMin.y > b.vMin.y ? a.vMin.y : b.vMin.y;
                vMin.z = a.vMin.z > b.vMin.z ? a.vMin.z : b.vMin.z;

                vMax.x = a.vMax.x < b.vMax.x ? a.vMax.x : b.vMax.x;
                vMax.y = a.vMax.y < b.vMax.y ? a.vMax.y : b.vMax.y;
                vMax.z = a.vMax.z < b.vMax.z ? a.vMax.z : b.vMax.z;

                Intersect.Set(vMin, vMax-vMin);
                if (Intersect == a || Intersect == b)
                {
                    return KCollisionType::RECT_IN;
                }
                return KCollisionType::RECT_OVERLAP;
            }
        }
    }
    return KCollisionType::RECT_OUT;
}
bool   KCollision::BoxToInBox(KBox& a, KBox& b)
{
    //  |             |
    if (a.vMin <= b.vMin)
    {
        if ( a.vMax >= b.vMax)
        {
            return true;
        }
    }
    return false;
}
bool             KCollision::SphereToSphere(KSphere& a, KSphere& b)
{
    float fSumRadius = a.fRadius + b.fRadius;
    KVector vDir = a.vCenter - b.vCenter;    
    float fDistance = vDir.Length();
    if (fDistance <= fSumRadius)
    {
        return true;
    }
    return false;
}