#pragma once
#include "KBaseObject.h"
#include "KVector.h"
#include"KCameraDebug.h"
class KMap :
    public KBaseObject
{
    DWORD_VECTOR indexlist;
public:
    bool Build(UINT iWidth, UINT iHeight);
    bool UpdateBuffer(KCameraDebug*pMainCamera);
};

