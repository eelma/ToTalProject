#pragma once
#include"KStd.h"
#include"KVector.h"

struct SimpleVertex
{
	KVector p;
	KVector4D c;
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
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;
public:
	HRESULT		CreateVertexBuffer();
	HRESULT		CreateShader();

	HRESULT     CreateVertexLayout();
public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
};
