#include "KFbxObject.h"
void  KFbxObject::CreateVertexData()
{
}
HRESULT KFbxObject::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	if (vbDataList.size() > 0)
	{
		m_pSubVB.resize(vbDataList.size());
		for (int ivb = 0; ivb < vbDataList.size(); ivb++)
		{
			if (vbDataList[ivb].size() > 0)
			{
				m_pSubVB[ivb] =
					TDX::CreateVertexBuffer(m_pd3dDevice,
						&vbDataList[ivb].at(0),
						vbDataList[ivb].size(),
						sizeof(PNCT_VERTEX));
			}
		}
	}
	else
	{
		hr = KObject3D::CreateVertexBuffer();
	}
	return hr;
}
HRESULT KFbxObject::CreateIndexBuffer()
{
	return S_OK;
}
bool KFbxObject::LoadTexture(W_STR texturename)
{
	if (vbTexList.size() > 0)
	{
		W_STR szDefaultDir = L"../../data/fbx/";
		m_pSubTexture.resize(vbTexList.size());
		for (int ivb = 0; ivb < vbTexList.size(); ivb++)
		{
			W_STR szLoadFile = szDefaultDir + vbTexList[ivb];
			m_pSubTexture[ivb] = I_Tex.Load(szLoadFile);
		}
	}
	else
	{
		m_pTexture = I_Tex.Load(texturename);
		if (m_pTexture != nullptr)
		{
			m_pTextureSRV = m_pTexture->m_pTextureSRV;
			return true;
		}
	}return false;
}
bool KFbxObject::PostRender()
{
	if (m_pIndexBuffer == nullptr)
	{
		if (vbDataList.size() > 0)
		{
			for (int iSubObj = 0; iSubObj < m_pSubVB.size(); iSubObj++)
			{
				if (vbDataList[iSubObj].size() <= 0)continue;

				UINT stride = sizeof(PNCT_VERTEX);//정점1개의 바이트 용량
				UINT offset = 0;//정점버퍼에서 출발지점(바이트)
				//SLOT레지스터리
				m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pSubVB[iSubObj], &stride, &offset);
				if(m_pSubTexture[iSubObj]!=nullptr)
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
bool KFbxObject::Release()
{
	KObject3D::Release();
	for (int iSubObj = 0; iSubObj < m_pSubVB.size(); iSubObj++)
	{
		if (m_pSubVB[iSubObj])
		{
			m_pSubVB[iSubObj]->Release();
		}
	}
	return true;
}