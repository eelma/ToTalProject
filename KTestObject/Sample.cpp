#include "Sample.h"

bool Sample::Init()
{
	I_Shader.SetDevice(m_pd3dDevice, m_pImmediateContext);
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";

	m_pMap = new KMapObject;
	m_pMap->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/mapHeight.bmp");

	m_pUser = new KMapObject;
	m_pUser->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/bitmap1.bmp");

	/*for (int iObj = 0; iObj < 1; iObj++)
	{
		KBaseObject* pObj = new KBaseObject;
		pObj->Create(m_pd3dDevice,
			m_pImmediateContext,
			shaderfilename,
			L"../../data/air.bmp"
			);
		m_ObjectList.push_back(pObj);
	}*/
	/*for (int iObj = 0; iObj < 10; iObj++)
	{
		KBaseObject* pObj = new KBaseObject;
		pObj->Create(m_pd3dDevice,
			m_pImmediateContext,
			L"../../data/shader/DefaultShape.txt",
			L"../../data/bitmap1.bmp"
			);
		m_ObjectList.push_back(pObj);
	}*/


	
	return true;
}
bool Sample::Frame()
{
	m_pMap->Frame();
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj]->Frame();
	}
	return true;
}
bool Sample::Render()
{
	m_pMap->Render();
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj]->Render();
	}
	return true;
}
bool Sample::Release()
{
	m_pMap->Release();
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj]->Release();
		delete m_ObjectList[iObj];
	}
	/*for (int iObj = 0; iObj < m_ObjectTextureList.size(); iObj++)
	{
		m_ObjectTextureList[iObj]->Release();
		delete m_ObjectTextureList[iObj];
	}*/
	return true;
}

GAME_RUN(KTestTexture, 800, 600)