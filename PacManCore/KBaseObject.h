#pragma once
#include "KDevice.h"
#include"KTextureManager.h"
#include"KShaderManager.h"
#include"KCollision.h"
struct SimpleVertex
{
	KVector    p;
	KVector4D  c;
	KVector2D  t;
};

class KBaseObject
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	KTexture* m_pTexture;
	KShader* m_pShader;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;

public:
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;
	KRect m_rtCollision;



	vector<SimpleVertex>    m_VertexList;
	vector<DWORD>			 m_IndexList;
public:
	virtual bool		Create(
		ID3D11Device* pd3dDevice,// 디바이스 객체
		ID3D11DeviceContext* pImmediateContext,
		wstring shadername, wstring texturename);
	virtual void		CreateVertexData();
	virtual void		CreateIndexData();
	virtual HRESULT		CreateVertexBuffer();
	virtual HRESULT		CreateIndexBuffer();
	virtual HRESULT     CreateVertexShader(wstring filename);
	virtual HRESULT     CreatePixelShader(wstring filename);
	virtual bool		CreateShader(wstring filename);
	virtual HRESULT     CreateVertexLayout();
	virtual void		UpdateVertexBuffer();
public:
	virtual bool		Init();
	virtual bool		Frame();

	virtual bool		Render();
	virtual bool		PreRender();
	virtual bool		PostRender();
	
	virtual bool		Release();
};

