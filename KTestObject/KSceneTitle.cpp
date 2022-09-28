#include "KSceneTitle.h"

bool KSceneTitle::Init()
{
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	//KTexture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	m_pMap = new KMapObject;
	m_pMap->Create(m_pd3dDevice,
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
	m_pMap->Render();

	return true;
}
bool KSceneTitle::Release()
{
	m_pMap->Release();
	
	return true;
}
