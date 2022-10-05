#pragma once

#include"KMapObject.h"
#include"KUser2D.h"
#include"KNpc2D.h"
#include"KStaticObject.h"
static float score = 0;
class KScene:public KSingleTone<KScene>
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
public:
	KUser2D* m_pUser;
	KMapObject* m_pMap;
	KStaticObject* m_pstatic;
	list <KStaticObject*> m_StaticList;
	wstring xy;
public:
	virtual bool		Create(
		ID3D11Device* pd3dDevice,// 디바이스 객체
		ID3D11DeviceContext* pImmediateContext,
		wstring shadername);
	void InitNPC();
	void InitMapObj();
public:
	//std::vector<KBaseObject*>	m_pNpcList;
	vector<KTexture*>		m_ObjectTextureList;
	list<KNpc2D*> m_pNpcList;
	
	KVector2D		m_vCamera;
	//KUser2D* m_pUser;

public:
	virtual bool		Init() ;
	virtual bool		Frame() ;
	virtual bool		Render() ;
	virtual bool		Release() ;
};
