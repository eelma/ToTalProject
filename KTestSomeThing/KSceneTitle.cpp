#include "KSceneTitle.h"
#include "KInput.h"
bool       KSceneTitle::IsNextScene()
{
	return false;
}
bool KSceneTitle::Init()
{
	wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	m_pBG = new KBaseObject;
	m_pBG->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/gameHeight.png");
	return true;
}
bool KSceneTitle::Frame()
{
	KMatrix m, s, t, c;
	float fScale=cos(g_fGameTimer)*0.5f+0.5f;
	s = s.Scale(fScale, fScale, fScale);
	m = m.RotationZ(g_fGameTimer);
	t = t.Translation(0.5f, 0.0f, 0.0f);
	c = s * m * t;
	for (int i = 0; i < m_pBG->m_InitVertexList.size(); i++)
	{
		KVector v = m_pBG->m_InitVertexList[i].p;
		//v = v * s; // s * r * t 		
		//v = v * m;
		//v = v * t;
		m_pBG->m_VertexList[i].p = v*c;
	}
	m_pBG->UpdateVertexBuffer();


	return true;
}
bool KSceneTitle::Render()
{
	m_pBG->Render();
	return true;
}
bool KSceneTitle::Release()
{
	m_pBG->Release();
	return true;
}