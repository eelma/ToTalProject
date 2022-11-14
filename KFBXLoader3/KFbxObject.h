#pragma once
#include<fbxsdk.h>
#include"KObject3D.h"
struct KAnimTrack
{
	UINT iFrame;//fTime
	TMatrix matAnim;//self*parent;
	TMatrix matSelfAnim;//matAnim*inv(parent)
	TVector3 t;
	TQuaternion r;
	TVector3 s;
};
struct KAnimScene
{
	FbxTime::EMode TimeMode;
	UINT iStartFrame;
	UINT iEndFrame;
	float fTickPerFrame;
	float fFrameSpeed;
};
struct KWeight
{
	vector<int >Index;
	vector<float>weight;
	void insert(int iBonde, float fWeight)
	{
		for (int i = 0; i < Index.size(); i++)
		{
			if (fWeight > weight[i])
			{
				for (int j = Index.size() - 1; j < i; j++)
				{
					Index[j] = Index[j - 1];
					weight[j] = weight[j - 1];
				}
				Index[i] = iBonde;
				weight[i] = fWeight;
				break;
			}
		}
	}
	KWeight()
	{
		Index.resize(8);
		weight.resize(8);
	}
};
class KFbxObject
{
public:
	UINT m_iObjectBone;
	TMatrix m_matAnim;
	TMatrix m_matControl;

	FbxAMatrix m_fbxLocalMatrix;
	FbxNode* m_pFbxNode = nullptr;
	FbxNode* m_pFbxParentNOde = nullptr;
	KFbxObject* m_pParent = nullptr;
	vector<KFbxObject*> m_pFbxChilds;
	vector<KAnimTrack>m_AnimTracks;
	void SetParent(KFbxObject* pParentNode)
	{
		pParentNode->m_pFbxChilds.push_back(this);
		m_pParent = pParentNode;
	}


public:
	vector<ID3D11Buffer*>m_pSubVB;
	vector<vector<PNCT_VERTEX>>vbDataList;
	vector<KTexture*>m_pSubTexture;
	vector<W_STR> vbTexList;
public:
	void CreateVertexDate();
	HRESULT CreteVertexBufer();
	HRESULT CreateIndexBuffer();
	bool LoadTexture(W_STR texturename);
	bool PostRender();
	bool Release();
	TMatrix Interplate(float fTime, KAnimScene kScene);
};
class KFbxObjectSkinning : public KFbxObject
{

public:
	bool m_bSkinned = false;
	//¼­ºê ¸ÞÅ×¸®¾ó
	vector<ID3D11Buffer*>m_pSubVB_IW;
	vector<vector<IW_VERTEX>> vbDataList_IW;
	//½Ì±Û ¸ðµ¨
	vector<IW_VERTEX> m_VertexListIW;
	ID3D11Buffer* m_pVertexBufferIW;
	//½ºÅ°´×
	vector<KWeight>m_WeightList;
	map<UINT, TMatrix>m_dxMatrixBindPseMap;

public:
	VS_CONSTANT_BONE_BUFFER m_cbDataBone;
	ID3D11Buffer* m_pSkinBondeCB;
public:
	HRESULT CreateConstantBuffer()
	{
		KObject3D::CreateConstantBuffer();
		HRESULT hr;
		for (int iBone = 0; iBone < 255; iBone++)
		{

			D3DXMatrixIdentity(&m_cbDataBone.matBone[iBone]);

		}
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(VS_CONSTANT_BONE_BUFFER)*1;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = &m_cbDataBone;
		hr = m_pd3dDevice->CreateBuffer(
			&bd, &sd, &m_pSkinBondeCB
		);
		return hr;
	}

};

