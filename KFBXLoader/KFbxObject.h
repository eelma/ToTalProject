#pragma once
#include<fbxsdk.h>
#include "KObject3D.h"
struct KAnimTrack
{
	UINT iFrame;//ftime
	TMatrix matAnim;//self*parent
	TMatrix matSelfAnim;//matanum*inv(parent)
	TVector3 t;//self
	TQuaternion r;//self
	TVector3 s;//self
};
struct KAnimScene
{
	UINT iStartFarame;
	UINT iEndFrame;
	float fTickPerFrame;//160
	float fFrameSpeed;//30
};
class KFbxObject : public KObject3D
{
public:
	TMatrix m_matAnim;
	TMatrix m_matControl;
	KAnimScene m_AnimScene;
public:
	float m_fAnimFrame = 0;
	float m_fAnimInverse = 1.0f;
	float m_fAnimSpeed = 1.0f;
	FbxAMatrix m_fbxLocalMatrix;
	FbxNode* m_pFbxNode = nullptr;
	FbxNode* m_pFbxParentNode = nullptr;
	KFbxObject* m_pParent = nullptr;
	vector<KFbxObject*>m_pFbxChilds;
	vector<KAnimTrack>m_AnimTracks;
	void SetParent(KFbxObject* pParentNode)
	{
		pParentNode->m_pFbxChilds.push_back(this);
		m_pParent = pParentNode;
	}
	TMatrix Interplate(float fTime);
public:
	vector<ID3D11Buffer*> m_pSubVB;
	vector<vector<PNCT_VERTEX>> vbDataList;
	vector<KTexture*>m_pSubTexture;
	vector<W_STR> vbTexList;
public:
	void  CreateVertexData();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	bool LoadTexture(W_STR texturename);
	bool PostRender();
	bool Release();
};
