#include "KSceneTitle.h"
bool KSceneTitle::Init()
{
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	m_pMapTitle = new KBaseObject;
	m_pMapTitle->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/kgcabk.bmp");
	return true;
}
bool KSceneTitle::Frame()
{
	return true;
}
bool KSceneTitle::Render()
{
	m_pMapTitle->Render();
	return true;
}
bool KSceneTitle::Release()
{
	m_pMapTitle->Release();
	return true;
}