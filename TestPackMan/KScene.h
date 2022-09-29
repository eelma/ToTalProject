#pragma once

#include"KMapObject.h"
#include"KUser2D.h"
#include"KNpc2D.h"

class KScene
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;// ����̽� ��ü
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
public:
	KUser2D* m_pUser;
	KMapObject* m_pMap;
public:
	virtual bool		Create(
		ID3D11Device* pd3dDevice,// ����̽� ��ü
		ID3D11DeviceContext* pImmediateContext,
		std::wstring shadername);
public:
	std::vector<KBaseObject*>	m_pNpcList;
	std::vector<KTexture*>		m_ObjectTextureList;

public:
	virtual bool		Init() ;
	virtual bool		Frame() ;
	virtual bool		Render() ;
	virtual bool		Release() ;
};