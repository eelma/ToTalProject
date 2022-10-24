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

void KObjectBox::SetMatrix(KMatrix* matWorld, KMatrix* matView, KMatrix* MatProj)
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
	m_VertexList[23]= SimpleVertex(KVector(-1.0f, -1.0f, 1.0f), KVector4(1.0f, 0.0f, 0.0f, 1.0f), KVector2(0.0f, 0.0f));

}

void KObjectBox::CreateVertexData()
{
}

void KObjectBox::CreateIndexData()
{
}
