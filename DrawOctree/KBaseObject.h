#pragma once
#include"KStd.h"
#include"KVector.h"
#include"KCollision.h"

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
	virtual bool		Create(); // �ʱ�ȭ
	virtual bool		Init(); // �ʱ�ȭ
	virtual bool		Frame();// �ǽð� ���
	virtual bool		Frame(float fDeltaTime, float fGameTime) { return true; };
	virtual bool		Render();// �ǽð� ������
	virtual bool		Release();// �Ҹ� �� ����


public:
	std::string  m_csName;
	float       m_fFriction;
	float       m_fMass;
	float       m_fSpeed;
public:
	KVector    m_vDirection;
	KBox       m_Box;
	KSphere    m_Sphere;
	KVector    m_vAcceleration;
	KVector    m_vVelocity;
	KVector    m_vForces;
public:
	KVector2D   m_vDirection2D;
	KRect       m_rt;
	KCircle     m_Circle;
	KVector2D   m_vAcceleration2D;
	KVector2D   m_vVelocity2D;
	KVector2D   m_vForces2D;
public:
	KBaseObject();
	virtual ~KBaseObject();

};
