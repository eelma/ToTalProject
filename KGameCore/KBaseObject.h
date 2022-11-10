#pragma once
#include"TMath.h"
#include "KDevice.h"
#include"KTextureManager.h"
#include"KShaderManager.h"
#include"KCollision.h"
struct SimpleVertex
{
	TVector3    p;
	TVector4  c;
	TVector2  t;
	SimpleVertex() {}
	SimpleVertex(TVector3 vp,TVector4 vc, TVector2 vt)
	{
		p = vp;
		c = vc;
		t = vt;
	}
};
struct PNCT_VERTEX
{
	TVector3   p;
	TVector3	  n;
	TVector4  c;
	TVector2  t;
	PNCT_VERTEX() {}
	PNCT_VERTEX(TVector3 vp, TVector3 vn, TVector4 vc, TVector2 vt)
	{
		p = vp;
		n = vn;
		c = vc;
		t = vt;
	}
};
struct VS_CONSTANT_BUFFER
{
	TMatrix  matWorld;
	TMatrix  matView;
	TMatrix  matProj;

	float    x;
	float    y;
	float	 z;
	float    fTimer;
};
struct IW_VERTEX
{
	TVector4 w;
	TVector4 i;
	IW_VERTEX(){}
	IW_VERTEX(TVector4 vIndex, TVector4 vWeight)
	{
		w = vWeight;
		i = vIndex;
	}
};
struct VS_CONSTANT_BONE_BUFFER
{
	TMatrix matBone[255];
};
	namespace TDX
{
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* pd3dDevice,
		void* pDataAddress,
		UINT iNumVertex,
		UINT iVertexSize);
	//dx와 관련된 기능만 있음
	class KBaseObject
	{
	public:

		bool		m_IsNullable = true;
	public:
		TMatrix		m_matWorld;
		TMatrix		m_matView;
		TMatrix		m_matProj;
		DWORD m_dwFace;
	public:
		ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
		ID3D11DeviceContext* m_pImmediateContext = nullptr;
		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
		ID3D11InputLayout* m_pVertexLayout;
		KTexture* m_pTexture;
		KShader* m_pShader;
		wstring m_szShaderName;
		wstring m_szTextureName;
		ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
		VS_CONSTANT_BUFFER  m_cbData;
		ID3D11Buffer* m_pConstantBuffer;



	public:
		ID3D11VertexShader* m_pVS;
		ID3D11PixelShader* m_pPS;
		ID3DBlob* m_pVSCode = nullptr;
		ID3DBlob* m_pPSCode = nullptr;

		vector<PNCT_VERTEX>    m_VertexList;
		vector<PNCT_VERTEX>    m_InitVertexList;
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
		virtual void		SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj);
		virtual bool		LoadTexture(W_STR texturename);

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
};
using namespace TDX;

