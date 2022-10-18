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
		L"../../data/KGCABK.bmp");
	return true;
}
bool KSceneTitle::Frame()
{
	KMatrix matView;
	static KVector vPos = { 0,0,-10 };
	static KVector vTarget = { 0,0,10 };
	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		vPos.z += 10.0f * g_fSecondPerFrame;
		vTarget.z += 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('S') == KEY_HOLD)
	{
		vPos.z -= 10.0f * g_fSecondPerFrame;
		vTarget.z -= 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		vPos.x -= 10.0f * g_fSecondPerFrame;
		vTarget.x -= 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		vPos.x += 10.0f * g_fSecondPerFrame;
		vTarget.x += 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('Q') == KEY_HOLD)
	{
		vPos.y += 10.0f * g_fSecondPerFrame;
		vTarget.y += 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('E') == KEY_HOLD)
	{
		vPos.y -= 10.0f * g_fSecondPerFrame;
		vTarget.y -= 10.0f * g_fSecondPerFrame;
	}
	KVector vUp = { 0,1,0 };
	//https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
	matView.ViewLookAt(vPos, vTarget, vUp);
	
	KMatrix matProj;
	//원근 투영 행렬
	matProj.PerspectiveFovLH(1.0f,100.0f, 3.141592f * 0.5f,800.0f/600.0f);
	//matProj.OrthoLH(800, 600, 0.0f, 100.0f);
	//matProj.OrthoOffCenterLH(-400, 400, -300, 300, 0.0f, 100.0f);
	
	KMatrix m, s, t, c;
	float fScale = cos(g_fGameTimer) * 0.5f + 0.5f;
	//s = KMath::Scale(400,300,10);
	//s = s.Scale(10, 10, 10);
	//m = m.RotationZ(g_fGameTimer);
	////TVector vObjPos = { 0,0,0 };
	////TVector vObjTarget = { 0,5,5 };
	////m.ObjectLookAt(vObjPos, vObjTarget, vUp);
	//t = t.Translation(0.0f, 0, 0);
	c = s * m * t;
	for (int i = 0; i < m_pBG->m_InitVertexList.size(); i++)
	{
		KVector v = m_pBG->m_InitVertexList[i].p;
		//v = v * s; // s * r * t 		
		//v = v * m;
		//v = v * t;
		KVector vWorld = v * c;
		KVector vView = vWorld * matView;
		KVector vProj = vView * matProj;
		float w = vProj.x * matProj._14 + vProj.y * matProj._24 + vProj.z * matProj._34 + 1.0f * matProj._44;
		vProj.x /= w;
		vProj.y /= w;
		vProj.z /= w;
		m_pBG->m_VertexList[i].p = vProj;	
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