#pragma once
#include "mWindow.h"
class mDevice :public mWindow
{
public:
	
	ComPtr<IDXGIFactory> m_pGIFactory = nullptr;
	ComPtr<ID3D11Device> m_pd3dDevice = nullptr;//����̽� ��ü
	ComPtr<ID3D11DeviceContext> m_pImmediateContext = nullptr;

	ComPtr<IDXGISwapChain> m_pSwapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> m_pRTV = nullptr;

public:
	//1. ����̽� ����
	HRESULT CreateDevice();
	//2. ���丮 ����
	HRESULT CreateDXGIDevice();
	//3. ����ü�� ����
	HRESULT CreateSwapChain();
	//4. ����Ÿ�ٺ� ����
	HRESULT CreateRenderTargetView();
	//5. ����Ʈ ����
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

