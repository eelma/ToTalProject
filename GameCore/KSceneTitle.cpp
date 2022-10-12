#include "KSceneTitle.h"

bool KSceneTitle::Init()
{
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	m_pMap = new KMapObject;
	m_pMap->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/white.png");


	return true;
}
bool KSceneTitle::Frame()
{

	return true;
}
bool KSceneTitle::Render()
{
	m_pMap->Render();

	return true;
}
bool KSceneTitle::Release()
{
	m_pMap->Release();
	
	return true;
}
