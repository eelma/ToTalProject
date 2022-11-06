#include "KShape.h"
#include"KInput.h"

void KShapeBox::CreateVertexData()
{
	m_VertexList.resize(24);
	m_VertexList[0] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[1] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[2] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[3] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 1.0f));
	// 뒷면														 				
	m_VertexList[4] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[5] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[6] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[7] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 1.0f));

	// 오른쪽													 		  		  
	m_VertexList[8] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(1.0f, 0.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[9] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(1.0f, 0.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[10] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(1.0f, 0.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[11] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(1.0f, 0.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 1.0f));

	// 왼쪽																		
	m_VertexList[12] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[13] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(-1.0f, 0.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[14] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(-1.0f, 0.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[15] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 1.0f));
	//위																				
	m_VertexList[16] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[17] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[18] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[19] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 1.0f));
	//아래																		
	m_VertexList[20] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(0.0f, -1.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[21] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(0.0f, -1.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[22] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(0.0f, -1.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(1.0f, 1.0f));
	m_VertexList[23] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(0.0f, -1.0f, 0.0f), KVector4(1.0f, 1.0f, 1.0f, 1.0f), KVector2(0.0f, 1.0f));



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

	//KMatrix m, s, t, c;
	//float fScale = cos(g_fGameTimer) * 0.5f + 0.5f;
	//s = KMath::Scale(400, 300, 10);
	//m = KMath::RotationZ(g_fGameTimer);
	//t = KMath::Translation(0.0f, 0, 0);
	//m_matWorld = s * m * t;
	m_cbData.fTimer = g_fGameTimer;	

	return true;
}

bool KShapeBox::Render()
{

	PreRender();
	PostRender();
	
	return true;
}

void KShapeLine::CreateVertexData()
{
	//상단
	//5  6
	//1  2
	//하단
	//4  7
	//0  3
	//앞면
	m_VertexList.resize(2);
	m_VertexList[0] = PNCT_VERTEX(TVector3(0.0f, 0.0f, 0.0f),    TVector3(0.0f,0.0f,-1.0f),KVector4(1.0, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[1] = PNCT_VERTEX(TVector3(0.0f, 0.0f, 1000.0f), TVector3(0.0f,0.0f,-1.0f),KVector4(1.0, 0.0f, 0.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_InitVertexList = m_VertexList;
}
void KShapeLine::CreateIndexData()
{
	m_IndexList.resize(2);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0;
	m_IndexList[iIndex++] = 1;
}
bool KShapeLine::Render()
{
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	PreRender();
	PostRender();
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}
bool KShapeLine :: Frame()
{
	m_cbData.fTimer = g_fGameTimer;
	return true;
}
void KShapeDirectionLine::CreateVertexData()
{
	//상단
	//5  6
	// 1  2
	// 하단
	// 4  7
	// 0  3
	// 앞면
	m_VertexList.resize(6);
	m_VertexList[0] = PNCT_VERTEX(TVector3(0.0f, 0.0f, 0.0f),TVector3(0.0f,0.0f,-1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[1] = PNCT_VERTEX(TVector3(1.0f, 0.0f, 0.0f),TVector3(0.0f,0.0f,-1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[2] = PNCT_VERTEX(TVector3(0.0f, 0.0f, 0.0f),TVector3(0.0f,0.0f,-1.0f), KVector4(0.0f, 1.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[3] = PNCT_VERTEX(TVector3(0.0f, 1.0f, 0.0f),TVector3(0.0f,0.0f,-1.0f), KVector4(0.0f, 1.0f, 0.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_VertexList[4] = PNCT_VERTEX(TVector3(0.0f, 0.0f, 0.0f),TVector3(0.0f,0.0f,-1.0f), KVector4(0.0f, 0.0f, 1.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[5] = PNCT_VERTEX(TVector3(0.0f, 0.0f, 1.0f),TVector3(0.0f,0.0f,-1.0f), KVector4(0.0f, 0.0f, 1.0f, 1.0f), KVector2(1.0f, 0.0f));
	m_InitVertexList = m_VertexList;
}
void KShapeDirectionLine::CreateIndexData()
{
	m_IndexList.resize(6);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; m_IndexList[iIndex++] = 1;
	m_IndexList[iIndex++] = 2; m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; m_IndexList[iIndex++] = 5;
	

}




//KMatrix matView;
//static TVector3 vPos = { 0,0,-10 };
//static TVector3 vTarget = { 0,0,10 };
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
//TVector3 vUp = { 0,1,0 };
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
//////TVector3 vObjPos = { 0,0,0 };
//////TVector3 vObjTarget = { 0,5,5 };
//////m.ObjectLookAt(vObjPos, vObjTarget, vUp);
////t = t.Translation(0.0f, 0, 0);
//c = s * m * t;
//m_cbData.matWorld = c;
//m_cbData.matView = matView;
//m_cbData.matProj = matProj;
//m_cbData.fTimer = g_fGameTimer;
//UpdateConstantBuffer();
//return true;
