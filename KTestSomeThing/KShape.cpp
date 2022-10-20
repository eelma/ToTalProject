#include "KShape.h"
#include"KInput.h"

void KShapeBox::CreateVertexData()
{
	m_VertexList.resize(24);
	m_VertexList[0] = SimpleVertex(KVector(-1.0f, 1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[1] = SimpleVertex(KVector(1.0f, 1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[2] = SimpleVertex(KVector(1.0f, -1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[3] = SimpleVertex(KVector(-1.0f, -1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 1.0f));
	// 뒷면
	m_VertexList[4] = SimpleVertex(KVector(1.0f, 1.0f, 1.0f), KVector4(0.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[5] = SimpleVertex(KVector(-1.0f, 1.0f, 1.0f), KVector4(0.0f, 1.0f, 0.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[6] = SimpleVertex(KVector(-1.0f, -1.0f, 1.0f), KVector4(0.0f, 1.0f, 0.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[7] = SimpleVertex(KVector(1.0f, -1.0f, 1.0f), KVector4(0.0f, 1.0f, 0.0f, 1.0f), KVector2(0.0f, 1.0f));

	// 오른쪽
	m_VertexList[8] = SimpleVertex(KVector(1.0f, 1.0f, -1.0f), KVector4(0.0f, 0.0f, 1.0f, 1.0f),  KVector2(0.0f, 0.0f));
	m_VertexList[9] = SimpleVertex(KVector(1.0f, 1.0f, 1.0f), KVector4(0.0f, 0.0f, 1.0f, 1.0f),	  KVector2(1.0f, 0.0f));
	m_VertexList[10] = SimpleVertex(KVector(1.0f, -1.0f, 1.0f), KVector4(0.0f, 0.0f, 1.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[11] = SimpleVertex(KVector(1.0f, -1.0f, -1.0f), KVector4(0.0f, 0.0f, 1.0f, 1.0f), KVector2(0.0f, 1.0f));

	// 왼쪽
	m_VertexList[12] = SimpleVertex(KVector(-1.0f, 1.0f, 1.0f), KVector4(1.0f, 1.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[13] = SimpleVertex(KVector(-1.0f, 1.0f, -1.0f), KVector4(1.0f, 1.0f, 0.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[14] = SimpleVertex(KVector(-1.0f, -1.0f, -1.0f), KVector4(1.0f, 1.0f, 0.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[15] = SimpleVertex(KVector(-1.0f, -1.0f, 1.0f), KVector4(1.0f, 1.0f, 0.0f, 1.0f), KVector2(0.0f, 1.0f));
	//위
	m_VertexList[16] = SimpleVertex(KVector(-1.0f, 1.0f, 1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[17] = SimpleVertex(KVector(1.0f, 1.0f, 1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[18] = SimpleVertex(KVector(1.0f, 1.0f, -1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[19] = SimpleVertex(KVector(-1.0f, 1.0f, -1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 1.0f));
	//아래
	m_VertexList[20] = SimpleVertex(KVector(1.0f, -1.0f, 1.0f),  KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[21] = SimpleVertex(KVector(-1.0f, -1.0f, 1.0f),   KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[22] = SimpleVertex(KVector(-1.0f, -1.0f, -1.0f),  KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[23] = SimpleVertex(KVector(1.0f, -1.0f, -1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 1.0f));
	


	m_InitVertexList = m_VertexList;
}

void KShapeBox::CreateIndexData()
{
	m_IndexList.resize(36);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;


}

bool KShapeBox::Frame()
{

	//KMatrix matView;
	//static KVector vPos = { 0,0,-10 };
	//static KVector vTarget = { 0,0,10 };
	//if (I_Input.GetKey('W') == KEY_HOLD)
	//{
	//	vPos.z += 10.0f * g_fSecondPerFrame;
	//	vTarget.z += 10.0f * g_fSecondPerFrame;
	//}
	//if (I_Input.GetKey('S') == KEY_HOLD)
	//{
	//	vPos.z -= 10.0f * g_fSecondPerFrame;
	//	vTarget.z -= 10.0f * g_fSecondPerFrame;
	//}
	//if (I_Input.GetKey('A') == KEY_HOLD)
	//{
	//	vPos.x -= 10.0f * g_fSecondPerFrame;
	//	vTarget.x -= 10.0f * g_fSecondPerFrame;
	//}
	//if (I_Input.GetKey('D') == KEY_HOLD)
	//{
	//	vPos.x += 10.0f * g_fSecondPerFrame;
	//	vTarget.x += 10.0f * g_fSecondPerFrame;
	//}
	//if (I_Input.GetKey('Q') == KEY_HOLD)
	//{
	//	vPos.y += 10.0f * g_fSecondPerFrame;
	//	vTarget.y += 10.0f * g_fSecondPerFrame;
	//}
	//if (I_Input.GetKey('E') == KEY_HOLD)
	//{
	//	vPos.y -= 10.0f * g_fSecondPerFrame;
	//	vTarget.y -= 10.0f * g_fSecondPerFrame;
	//}
	//KVector vUp = { 0,1,0 };
	////https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
	//matView.ViewLookAt(vPos, vTarget, vUp);

	//KMatrix matProj;
	////원근 투영 행렬
	//matProj.PerspectiveFovLH(1.0f, 100.0f, 3.141592f * 0.5f, 800.0f / 600.0f);
	////matProj.OrthoLH(800, 600, 0.0f, 100.0f);
	////matProj.OrthoOffCenterLH(-400, 400, -300, 300, 0.0f, 100.0f);

	//KMatrix m, s, t, c;
	//float fScale = cos(g_fGameTimer) * 0.5f + 0.5f;
	////s = KMath::Scale(400,300,10);
	////s = s.Scale(10, 10, 10);
	////m = m.RotationZ(g_fGameTimer);
	//////KVector vObjPos = { 0,0,0 };
	//////KVector vObjTarget = { 0,5,5 };
	//////m.ObjectLookAt(vObjPos, vObjTarget, vUp);
	////t = t.Translation(0.0f, 0, 0);
	//c = s * m * t;
	//m_cbData.matWorld = c;
	//m_cbData.matView = matView;
	//m_cbData.matProj = matProj;
	//m_cbData.fTimer = g_fGameTimer;
	//UpdateConstantBuffer();
	//return true;

	KMatrix m, s, t, c;
	float fScale = cos(g_fGameTimer) * 0.5f + 0.5f;
	//s = TMath::Scale(400, 300, 10);
	//m = TMath::RotationZ(g_fGameTimer);
	//t = TMath::Translation(0.0f, 0, 0);
	c = s * m * t;
	m_matWorld = s * m * t;
	m_cbData.fTimer = g_fGameTimer;

	return true;
}

bool KShapeBox::Render()
{

	PreRender();
	PostRender();
	
	return true;
}
