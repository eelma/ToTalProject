#include "KObject3D.h"

bool KObjectBox::Init()
{
	m_pDirLineShape = new KShapeDirectionLine;
	m_pDirLineShape->Create(m_pd3dDevice, m_pImmediateContext, L"DefaultShape.txt", L"");
	return true;
}

bool KObjectBox::Frame()
{
	return true;
}

bool KObjectBox::Render()
{
	KBaseObject::Render();
	m_pDirLineShape->Render();
	return true;
}

bool KObjectBox::Release()
{
	if (m_pDirLineShape)m_pDirLineShape->Release();
	delete m_pDirLineShape;
	KBaseObject::Release();
	return true;
}

void KObjectBox::SetMatrix(KMatrix* matWorld, KMatrix* matView, KMatrix* matProj)
{
	KBaseObject::SetMatrix(matWorld, matView, matProj);
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	m_vRight.x = m_matWorld._11;
	m_vRight.y = m_matWorld._12;
	m_vRight.z = m_matWorld._13;

	m_vUp.x = m_matWorld._21;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._23;

	m_vLook.x = m_matWorld._31;
	m_vLook.y = m_matWorld._32;
	m_vLook.z = m_matWorld._33;

	KVector m_vUp;
	KVector m_vRight;
	KMatrix matLineWorld;
	matLineWorld.Scale(2.0f, 2.0f, 2.0f);
	matLineWorld = matLineWorld * m_matWorld;
	if (m_pDirLineShape)m_pDirLineShape->SetMatrix(&matLineWorld, matView, matProj);

}

void KObjectBox::CreateVertexData()
{

	//»ó´Ü
	//5  6
	//1  2
	//ÇÏ´Ü
	//4  7
	//0  3
	//¾Õ¸é
	m_VertexList.resize(24);
	//¾Õ¸é
	m_VertexList[0] = SimpleVertex(KVector(-1.0f, 1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[1] = SimpleVertex(KVector(1.0f, 1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[2] = SimpleVertex(KVector(1.0f, -1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[3] = SimpleVertex(KVector(-1.0f, -1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	//µÞ¸é
	m_VertexList[4] = SimpleVertex(KVector(1.0f, 1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[5] = SimpleVertex(KVector(-1.0f, 1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[6] = SimpleVertex(KVector(-1.0f, -1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[7] = SimpleVertex(KVector(1.0f, -1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	//¿À¸¥ÂÊ
	m_VertexList[8] = SimpleVertex(KVector(1.0f, 1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[9] = SimpleVertex(KVector(1.0f, 1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[10] = SimpleVertex(KVector(1.0f, -1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[11] = SimpleVertex(KVector(1.0f, -1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	//¿ÞÂÊ
	m_VertexList[12] = SimpleVertex(KVector(-1.0f, 1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[13] = SimpleVertex(KVector(-1.0f, 1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[14] = SimpleVertex(KVector(-1.0f, -1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[15] = SimpleVertex(KVector(-1.0f, -1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	//À­¸é
	m_VertexList[16] = SimpleVertex(KVector(-1.0f, 1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[17] = SimpleVertex(KVector(1.0f, 1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[18] = SimpleVertex(KVector(1.0f, 1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[19] = SimpleVertex(KVector(-1.0f, 1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	//¾Æ·§¸é
	m_VertexList[20] = SimpleVertex(KVector(-1.0f, -1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[21] = SimpleVertex(KVector(1.0f, -1.0f, -1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[22] = SimpleVertex(KVector(1.0f, -1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));
	m_VertexList[23] = SimpleVertex(KVector(-1.0f, -1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));

	m_InitVertexList = m_VertexList;
}

void KObjectBox::CreateIndexData()
{
	m_IndexList.resize(36);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; m_IndexList[iIndex++] = 1; m_IndexList[iIndex++] = 2; m_IndexList[iIndex++] = 0; m_IndexList[iIndex++] = 2; m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; m_IndexList[iIndex++] = 5; m_IndexList[iIndex++] = 6; m_IndexList[iIndex++] = 4; m_IndexList[iIndex++] = 6; m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; m_IndexList[iIndex++] = 9; m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8; m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;

}
