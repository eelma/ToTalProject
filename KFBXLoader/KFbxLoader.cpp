#include "KFbxLoader.h"
bool KFbxLoader::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
	return true;
}
bool KFbxLoader::Load(C_STR filename)
{
	m_pFbxImporter->Initialize(filename.c_str());
	m_pFbxImporter->Import(m_pFbxScene);
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode);

	for (auto mesh : m_pFbxMeshList)
	{
		ParseMesh(mesh);
	}
	return true;
}
void KFbxLoader::ParseMesh(FbxMesh* pFbxMesh)
{
	KFbxObject* pObject = new KFbxObject;

	// Layer °³³ä
	FbxLayerElementUV* VertexUVSet = nullptr;
	FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);
	if (pFbxLayer->GetUVs() != nullptr)
	{
		VertexUVSet = pFbxLayer->GetUVs();
	}

	int iNumPolyCount = pFbxMesh->GetPolygonCount();
	// 3 Á¤Á¡ -> 1Æú¸®°ï( »ï°¢Çü)
	// 4 Á¤Á¡ -> 1Æú¸®°ï( Äõµå )
	int iNumFace = 0;

	// Á¦¾îÁ¡
	FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
	for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
	{
		int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
		iNumFace = iPolySize - 2;
		for (int iFace = 0; iFace < iNumFace; iFace++)
		{
			int iCornerIndex[3];
			iCornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, 0);
			iCornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 2);
			iCornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 1);
			for (int iIndex = 0; iIndex < 3; iIndex++)
			{
				int vertexID = iCornerIndex[iIndex];
				FbxVector4 v = pVertexPositions[vertexID];
				SimpleVertex tVertex;
				tVertex.p.x = v.mData[0];
				tVertex.p.y = v.mData[2];
				tVertex.p.z = v.mData[1];
				tVertex.c = { 1,1,1,1 };
				FbxVector2 t = ReadTextureCoord(pFbxMesh, VertexUVSet);
				tVertex.t.x = t.mData[0];
				tVertex.t.y = 1.0f - t.mData[1];

				pObject->m_VertexList.push_back(tVertex);
			}
		}
	}

	m_pDrawObjList.push_back(pObject);
}
FbxVector2 KFbxLoader::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* VertexUVSet)
{
	FbxVector2 t;
	return t;
}
void KFbxLoader::PreProcess(FbxNode* pFbxNode)
{
	if (pFbxNode == nullptr) return;
	FbxMesh* pFbxMesh = pFbxNode->GetMesh();
	if (pFbxMesh)
	{
		m_pFbxMeshList.push_back(pFbxMesh);
	}
	int iNumChild = pFbxNode->GetChildCount();
	for (int iChild = 0; iChild < iNumChild; iChild++)
	{
		FbxNode* pChild = pFbxNode->GetChild(iChild);
		PreProcess(pChild);
	}
}
bool KFbxLoader::Frame()
{
	for (auto obj : m_pDrawObjList)
	{
		obj->Frame();
	}
	return true;
}
bool KFbxLoader::Render()
{
	for (auto obj : m_pDrawObjList)
	{
		obj->Render();
	}
	return true;
}

bool KFbxLoader::Release()
{
	for (auto obj : m_pDrawObjList)
	{
		obj->Release();
	}

	if(m_pFbxScene)m_pFbxScene->Destroy();
	if(m_pFbxImporter)m_pFbxImporter->Destroy();
	if(m_pFbxManager)m_pFbxManager->Destroy();
	return true;
}