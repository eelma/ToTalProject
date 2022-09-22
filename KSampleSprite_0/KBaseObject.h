#pragma once
#include"kTexture.h"
#include"KCollision.h"
#include"KShader.h"
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

	KTexture* m_pTexture;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	KShader* m_pShader;
	
public:
	HRESULT		CreateVertexBuffer();
	bool		CreateShader(wstring filename);
	HRESULT     CreateVertexLayout();
	bool		LoadTexture(wstring filename);
	
public:
	virtual bool		Init(); // �ʱ�ȭ
	virtual bool		Frame();// �ǽð� ���
	virtual bool		PostRender();// �ǽð� ������
	virtual bool		PreRender();// �ǽð� ������
	virtual bool		Render();// �ǽð� ������
	virtual bool		Release();// �Ҹ� �� ����
	virtual bool		Create(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pContext,
								const wchar_t* texName=0, const wchar_t* shaderName=0);

};
