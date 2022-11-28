#pragma once
#include"KFbxFile.h"
class KCharacter
{
public:
	UINT m_iFbxListID;
	KFbxFile* m_pFbxFile = nullptr;
public:
	TMatrix m_matWorld;
	TMatrix m_matView;
	TMatrix m_matProj;
public:
	KAnimScene m_AnimScene;
	float m_fAnimFrame = 0;
	UINT m_iStartFrame;
	UINT m_iEndFrame;
	float m_fAnimInverse = 1.0f;
	float m_fAnimSpeed = 1.0f;

	map<wstring, KAnimScene>m_ActionList;

	VS_CONSTANT_BONE_BUFFER m_cbDataBone;
	vector<VS_CONSTANT_BONE_BUFFER>m_cbDrawGeom;

	ID3D11Buffer* m_pAnimBoneCB;
	vector<ID3D11Buffer*>m_pSkinBondeCB;
public:
	HRESULT CreateConstantBuffer(ID3D11Device* pDevice);
	bool UpdateFrame(ID3D11DeviceContext* pCOntext);
	void SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj);
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();

};

