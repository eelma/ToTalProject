#pragma once
#include "KWindow.h"
class KDevice:public KWindow
{

    ID3D11Device* m_d3dDevice = nullptr;//����̽� ��ü
    ID3D11DeviceContext* m_lmmediateContext = nullptr;

    IDXGIFactory* m_GIFactory = nullptr;
    IDXGISwapChain* m_SwapChain = nullptr;

    ID3D11RenderTargetView* m_RTV = nullptr;
public:
    //1)����̽� ����
    HRESULT CreateDevice();
    //2)���丮 ����
    HRESULT CreateGXGIDevice();
    //3)����ü�� ����
    HRESULT CreateSwapChain();
    //4)����Ÿ�ٺ� ����
    HRESULT CreateRenderTargetView();
    //5)����Ʈ ����
    void CreateViewport();


public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

};

