#pragma once
#include "KDevice.h"


class Sample : public KDevice
{
    //�������̽�->�ϵ���� ���� ����->ȹ��
    //�ٷ��� new�� ����

public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

};

