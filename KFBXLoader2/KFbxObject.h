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
	FbxTime::EMode TimeMode;
	UINT iStartFrame;
	UINT iEndFrame;
	float fTickPerFrame;//160
	float fFrameSpeed;//30
};
class KFbxObject : public KObject3D
{
public:
	UINT m_iObjectBone;
	TMatrix m_matAnim;
	TMatrix m_matControl;
public:
	
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
	TMatrix Interplate(float fTime, KAnimScene kScene);
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

class KFbxObjectSkinning :public KFbxObject
{

public:
	vector<ID3D11Buffer*>m_pSubVB_IW;
	vector<vector<IW_VERTEX>> vbDataList_IW;
	vector<IW_VERTEX> m_VertexListIW;
	ID3D11Buffer* m_pVertexBufferIW;


	HRESULT CreateVertexLayout()
	{
		HRESULT hr;
		if (m_pVSCode == nullptr)
		{
			return E_FAIL;
		}
		// �������̾ƿ��� �������̴� ������ ����.
		// �������̾ƿ� ������ ������ �������̴� ������ �ʿ��ϴ�.
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,24,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,40,D3D11_INPUT_PER_VERTEX_DATA, 0},

			{"INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,16,D3D11_INPUT_PER_VERTEX_DATA, 0},

		};
		UINT NumElements = sizeof(ied) / sizeof(ied[0]);
		hr = m_pd3dDevice->CreateInputLayout(
			ied,
			NumElements,
			m_pVSCode->GetBufferPointer(),
			m_pVSCode->GetBufferSize(),
			&m_pVertexLayout);

		return hr;
	}
	HRESULT CreateVertexBuffer()
	{

		HRESULT hr = S_OK;
		KFbxObject::CreateVertexBuffer();

		if (vbDataList_IW.size() > 0)
		{

			m_pSubVB_IW.resize(vbDataList_IW.size());
			for (int ivb = 0; ivb < vbDataList_IW.size(); ivb++)
			{
				if (vbDataList_IW[ivb].size() > 0)
				{

					m_pSubVB_IW[ivb] =
						TDX::CreateVertexBuffer(m_pd3dDevice,
							&vbDataList_IW[ivb].at(0),
							vbDataList_IW[ivb].size(),
							sizeof(IW_VERTEX));
				}
			}

		}
		else
		{
			hr = KObject3D::CreateVertexBuffer();
		}
		return hr;
	}

	bool PostRender()
	{
		if (m_pIndexBuffer == nullptr)
		{
			if (vbDataList.size() > 0)
			{
				for (int iSubObj = 0; iSubObj < m_pSubVB.size(); iSubObj++)
				{
					if (vbDataList[iSubObj].size() <= 0)continue;
					UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(IW_VERTEX) };//���� 1���� ����Ʈ �뷮
					UINT offset[2] = { 0,0 };// �������ۿ��� �������(����Ʈ)
					//SLOT(�������͸�)
					ID3D11Buffer* buffer[2] = { m_pSubVB[iSubObj],m_pSubVB_IW[iSubObj] };
					m_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);

					if (m_pSubTexture.size()>0 && m_pSubTexture[iSubObj]!=nullptr)
					{
						m_pImmediateContext->PSSetShaderResources(0, 1, &m_pSubTexture[iSubObj]->m_pTextureSRV);
					}
					m_pImmediateContext->Draw(vbDataList[iSubObj].size(), 0);
				}
			}
			else
			{
				m_pImmediateContext->Draw(m_VertexList.size(), 0);
			}
		}
		else
		{
			m_pImmediateContext->DrawIndexed(m_dwFace * 3, 0, 0);
		}
		return true;
	}
	bool Release()
	{
		KObject3D::Release();
		if (m_pVertexBufferIW)m_pVertexBufferIW->Release();
		for (int iSubObj = 0; iSubObj < m_pSubVB.size(); iSubObj++)
		{
			if (m_pSubVB[iSubObj])
			{
				m_pSubVB[iSubObj]->Release();
				m_pSubVB_IW[iSubObj]->Release();
			}
		}
		return true;
	}

};