#include"KFbxFile.h"
HRESULT KFbxFile::CreateConstantBuffer(ID3D11Device* pDevice)
{
	HRESULT hr;
	for (int iBone = 0; iBone < 255; iBone++)
	{
		D3DXMatrixIdentity(&m_cbDataBone.matBone[iBone]);
	}
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VS_CONSTANT_BONE_BUFFER) * 1;
	//GPU에 할당
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_cbDataBone;
	hr = pDevice->CreateBuffer(
	&bd,//버퍼 할당
		&sd,//초기 할당된 버퍼를 채우는 cpu메모리 주소
		&m_pSkinBoneCB);
	return hr;
}
bool KFbxFile::UpdateFrame(ID3D11DeviceContext* pContext)
{
	m_fAnimFrame = m_fAnimFrame +
		g_fSecondPerFrame * m_fAnimSpeed * m_AnimScene.fFrameSpeed * m_fAnimInverse;
	if (m_fAnimFrame > m_AnimScene.iEndFrame ||
		m_fAnimFrame < m_AnimScene.iStartFrame)
	{
		m_fAnimFrame = min(m_fAnimFrame, m_AnimScene.iEndFrame);
		m_fAnimFrame = max(m_fAnimFrame, m_AnimScene.iStartFrame);
		m_fAnimInverse *= -1.0f;
	}
	//오브젝트+스키닝
	vector<TMatrix> matCurrentAnimList;
	for (int iBone = 0; iBone < m_pObjectList.size(); iBone++)
	{
		TMatrix matAnimation = m_pObjectList[iBone]->Interplate(m_fAnimFrame, m_AnimScene);
		D3DXMatrixTranspose(&m_cbDataBone.matBone[iBone], &matAnimation);
		matCurrentAnimList.push_back(matAnimation);
	}
	pContext->UpdateSubresource(m_pSkinBoneCB, 0, nullptr, &m_cbDataBone, 0, 0);
	//스키닝
	for (int iDraw = 0; iDraw < m_pDrawObjList.size(); iDraw++)
	{
		if (m_pDrawObjList[iDraw]->m_dxMatrixBindPseMap.size())
		{
			for (int iBone = 0; iBone < m_pObjectList.size(); iBone++)
			{
				auto iter = m_pDrawObjList[iDraw]->m_dxMatrixBindPseMap.find(iBone);
				if (iter != m_pDrawObjList[iDraw]->m_dxMatrixBindPseMap.end())
				{
					TMatrix matBind = iter->second;
					TMatrix matAnim = matBind * matCurrentAnimList[iBone];
					D3DXMatrixTranspose(&m_cbDataBone.matBone[iBone], &matAnim);
				}
			}
			pContext->UpdateSubresource(m_pDrawObjList[iDraw]->m_pSkinBoneCB
				, 0, nullptr, &m_cbDataBone, 0, 0);
		}

	}
	return true;
}
bool KFbxFile::Render()
{
	for (auto obj : m_pDrawObjList)
	{
		obj->Render();
	}
	return true;
}
