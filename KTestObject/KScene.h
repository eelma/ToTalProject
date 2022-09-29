#pragma once
#include "KMapObject.h"
#include "KUser2D.h"
#include "KNpc2D.h"
class KScene
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
public:
	KVector2D   m_vCamera = { 0, 0 };
	KUser2D* m_pUser;
	KRect       m_rtMap = { -1000.0f, -1000.0f, 2000.0f, 2000.0f };
public:
	virtual bool		Create(
		ID3D11Device* pd3dDevice,// 디바이스 객체
		ID3D11DeviceContext* pImmediateContext,
		std::wstring shadername);
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
};

