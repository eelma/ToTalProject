#pragma once
#include"KStd.h"
#include"KVector.h"
//p��ġ n�븻 c�÷� t�ؽ�ó��ǥ
struct SimpleVertex
{
	KVector p;
	KVector4D c;
	KVector2D t;
};
class KBaseObject
{
public:
	vector<SimpleVertex>m_VertexList;
	ID3D11Device* m_pd3dDevice = nullptr;// ����̽� ��ü
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	void SetDevice(
		ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext);
public:
	ID3D11Resource* m_Texture = nullptr;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;
public:
	HRESULT		CreateVertexBuffer();
	HRESULT		CreateShader(wstring filename);
	HRESULT     CreateVertexLayout();
	HRESULT		LoadTexture(wstring filename);
	
public:
	virtual bool		Init(); // �ʱ�ȭ
	virtual bool		Frame();// �ǽð� ���
	virtual bool		Render();// �ǽð� ������
	virtual bool		Release();// �Ҹ� �� ����
	virtual bool		Create(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pContext,
								const wchar_t* texName=0, const wchar_t* shaderName=0);

};
