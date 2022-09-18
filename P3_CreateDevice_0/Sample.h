#pragma once
#include "KDevice.h"


class Sample : public KDevice
{
    //인터페이스->하드웨어 직접 제어->획득
    //다렉은 new가 없다

public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

};

