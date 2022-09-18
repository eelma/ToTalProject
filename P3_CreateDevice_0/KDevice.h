#pragma once
#include "KWindow.h"
class KDevice:public KWindow
{

    ID3D11Device* m_d3dDevice = nullptr;//디바이스 객체
    ID3D11DeviceContext* m_lmmediateContext = nullptr;

    IDXGIFactory* m_GIFactory = nullptr;
    IDXGISwapChain* m_SwapChain = nullptr;

    ID3D11RenderTargetView* m_RTV = nullptr;
public:
    //1)디바이스 생성
    HRESULT CreateDevice();
    //2)팩토리 생성
    HRESULT CreateGXGIDevice();
    //3)스왑체인 생성
    HRESULT CreateSwapChain();
    //4)랜더타겟뷰 생성
    HRESULT CreateRenderTargetView();
    //5)뷰포트 생성
    void CreateViewport();


public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

};

