#pragma once
#include "mWindow.h"
class mDevice :public mWindow
{
public:
	
	ComPtr<IDXGIFactory> m_pGIFactory = nullptr;
	ComPtr<ID3D11Device> m_pd3dDevice = nullptr;//디바이스 객체
	ComPtr<ID3D11DeviceContext> m_pImmediateContext = nullptr;

	ComPtr<IDXGISwapChain> m_pSwapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> m_pRTV = nullptr;

public:
	//1. 디바이스 생성
	HRESULT CreateDevice();
	//2. 팩토리 생성
	HRESULT CreateDXGIDevice();
	//3. 스왑체인 생성
	HRESULT CreateSwapChain();
	//4. 랜더타겟뷰 생성
	HRESULT CreateRenderTargetView();
	//5. 뷰포트 설정
	void CreateViewport();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual HRESULT ResizeDevice(UINT width, UINT height);
	virtual HRESULT CreateDXResource();
	virtual HRESULT DeleteDXResource();



};

