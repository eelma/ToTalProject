#include "KScene.h"
bool		KScene::Create(
	ID3D11Device* pd3dDevice,// ����̽� ��ü
	ID3D11DeviceContext* pImmediateContext,
	std::wstring shadername)
{
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pImmediateContext;
	return true;
}
bool KScene::Init()
{
	return true;
}
bool KScene::Frame()
{
	return true;
}
bool KScene::Render()
{
	return true;
}
bool KScene::Release()
{
	return true;
}