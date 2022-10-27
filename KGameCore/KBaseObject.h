#pragma once
#include "KDevice.h"
#include"KTextureManager.h"
#include"KShaderManager.h"
#include"KCollision.h"
struct SimpleVertex
{
	KVector    p;
	KVector4  c;
	KVector2  t;
	SimpleVertex() {}
	SimpleVertex(KVector vp, KVector4 vc, KVector2 vt)
	{
		p = vp;
		c = vc;
		t = vt;
	}
};
struct VS_CONSTANT_BUFFER
{
	KMatrix  matWorld;
	KMatrix  matView;
	KMatrix  matProj;

	float    x;
	float    y;
	float    fTimer;
	float    d;
};
//dx와 관련된 기능만 있음
class KBaseObject
{
public:

	bool		m_IsNullable = true;
public:
	KMatrix		m_matWorld;
	KMatrix		m_matView;
	KMatrix		m_matProj;
	DWORD m_dwFace;
public:
	ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	KTexture* m_pTexture;
	KShader* m_pShader;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	VS_CONSTANT_BUFFER  m_cbData;
	ID3D11Buffer* m_pConstantBuffer;



public:
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;

	vector<SimpleVertex>    m_VertexList;
	vector<SimpleVertex>    m_InitVertexList;
	vector<DWORD>			 m_IndexList;
	KRect m_rtCollision;
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
	virtual void		CreateConstantData();
	virtual HRESULT		CreateConstantBuffer();
	virtual void		UpdateConstantBuffer();
	virtual void		SetMatrix(KMatrix* matWorld, KMatrix* matView, KMatrix* matProj);

public:
	virtual bool		Init();
	virtual bool		Frame();

	virtual bool		Render();
	virtual bool		PreRender();
	virtual bool		PostRender();
	
	virtual bool		Release();
public:
	KBaseObject()
	{
		m_IsNullable = false;
	}

};

