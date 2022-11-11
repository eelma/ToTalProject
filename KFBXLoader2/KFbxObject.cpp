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
TMatrix KFbxObject::Interplate(float fFrame, KAnimScene kScene)
{
	//10               20
	//a=0-------------b=20
	//t=0 ~ t=0.5  t=1
	KAnimTrack A, B;
	A = m_AnimTracks[max(kScene.iStartFrame, fFrame + 0)];
	B = m_AnimTracks[min(kScene.iEndFrame, fFrame + 1)];
	if (A.iFrame == B.iFrame)
	{
		return m_AnimTracks[fFrame].matAnim;
	}
	float t = (fFrame - A.iFrame)/(B.iFrame-A.iFrame);
	TVector3 pos;
	D3DXVec3Lerp(&pos, &A.t, &B.t, t);
	TVector3 scale;
	D3DXVec3Lerp(&scale, &A.s, &B.s, t);
	TQuaternion qRotation;
	D3DXQuaternionSlerp(&qRotation, &A.r, &B.r, t);

	TMatrix matScale;
	TMatrix matRotation;
	D3DXMatrixRotationQuaternion(&matRotation, &qRotation);

	TMatrix matCurrent = matRotation;
	matCurrent._41 = pos.x;
	matCurrent._42 = pos.y;
	matCurrent._43 = pos.z;
	return matCurrent;

}