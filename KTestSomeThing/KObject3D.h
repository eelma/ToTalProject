#pragma once
#include"KShape.h"
class KObject3D : public KBaseObject
{

public:
	KVector m_vPos;
	KVector m_vLook;
	KVector m_vUp;
	KVector m_vRight;

public:
	KObject3D() {};
	virtual ~KObject3D() {};
};

class KObjectBox :public KObject3D
{
public:
	KShape* m_pDirLineShape = nullptr;

public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
	virtual void SetMatrix(KMatrix* matWorld, KMatrix* matView, KMatrix* MatProj);
public:
	virtual void CreateVertexData()override;
	virtual void CreateIndexData()override;

public:
	KObjectBox() {};
	virtual ~KObjectBox() {};
};