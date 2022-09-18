#pragma once
#include "KDevice.h"

#include"DDSTextureLoader.h"
#include"WICTextureLoader.h"
#pragma comment(lib,"DirectXTK.lib")


class Sample : public KDevice

{
    //�������̽�->�ϵ���� ���� ����->ȹ��
    //�ٷ��� new�� ����

    ID3D11Resource* m_Texture=nullptr;
    ID3D11ShaderResourceView* m_pTextureSRV=nullptr;
   

public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

};

