#pragma once
#include "KDevice.h"

#include"DDSTextureLoader.h"
#include"WICTextureLoader.h"
#pragma comment(lib,"DirectXTK.lib")


class Sample : public KDevice

{
    //인터페이스->하드웨어 직접 제어->획득
    //다렉은 new가 없다

    ID3D11Resource* m_Texture=nullptr;
    ID3D11ShaderResourceView* m_pTextureSRV=nullptr;
   

public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

};

