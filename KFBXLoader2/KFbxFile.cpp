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
	//GPU�� �Ҵ�
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_cbDataBone;
	hr = pDevice->CreateBuffer(
	&bd,//���� �Ҵ�
		&sd,//�ʱ� �Ҵ�� ���۸� ä��� cpu�޸� �ּ�
		&m_pConstantBufferBone);
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

	for (int iBone = 0; iBone < m_pObjectList.size(); iBone++)
	{
		TMatrix matAnim = m_pObjectList[iBone]->Interplate(m_fAnimFrame, m_AnimScene);
		D3DXMatrixTranspose(&m_cbDataBone.matBone[iBone], &matAnim);
	}
	pContext->UpdateSubresource(m_pConstantBufferBone, 0, nullptr, &m_cbDataBone, 0, 0);
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
