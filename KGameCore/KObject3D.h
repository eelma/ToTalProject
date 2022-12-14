#pragma once
#include"KShape.h"
class KObject3D : public KBaseObject
{
public:
	W_STR     m_szName;
public:
	TVector3 m_vPos;
	TVector3 m_vLook;
	TVector3 m_vUp;
	TVector3 m_vRight;

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
	virtual void SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* MatProj);
public:
	virtual void CreateVertexData()override;
	virtual void CreateIndexData()override;

public:
	KObjectBox() {};
	virtual ~KObjectBox() {};
};