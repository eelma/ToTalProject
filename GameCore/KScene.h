#pragma once

#include"KMapObject.h"
#include"KUser2D.h"
#include"KNpc2D.h"
#include"KStaticObject.h"
#include"KWindow.h"
static float score = 0;
class KScene:public KSingleTone<KScene>
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
public:
	KUser2D* m_pUser;
	KMapObject* m_pMap;
	KStaticObject* m_pstatic;
	list <KStaticObject*> m_StaticList;
	wstring xy;
public:
	virtual bool		Create(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pImmediateContext,
		wstring shadername);
	void InitNPC();
	void InitMapObj();
public:
<<<<<<< HEAD:GameCore/KScene.h
=======
	//vector<KBaseObject*>	m_pNpcList;
>>>>>>> 48c3d63ff719d82e4eb39b8415a5f9bf170a0178:PacManCore/KScene.h
	vector<KTexture*>		m_ObjectTextureList;
	list<KNpc2D*> m_pNpcList;
	
	KVector2D		m_vCamera;
public:
	virtual bool		Init() ;
	virtual bool		Frame() ;
	virtual bool		Render() ;
	virtual bool		Release() ;
};
