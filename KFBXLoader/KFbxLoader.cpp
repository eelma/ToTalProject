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
	FbxNode* pNode = pFbxMesh->GetNode();
	KFbxObject* pObject = new KFbxObject;

	// Layer 개념
	FbxLayerElementUV* pUVSet = nullptr;
	FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);
	if (pFbxLayer->GetUVs() != nullptr)
	{
		pUVSet = pFbxLayer->GetUVs();
	}
	string szFileName;
	{
		FbxSurfaceMaterial* pSurface = pNode->GetMaterial(0);
		if (pSurface)
		{
			auto property = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (property.IsValid())
			{
				const FbxFileTexture* tex = property.GetSrcObject<FbxFileTexture>(0);
				if (property.IsValid())
				{
					const FbxFileTexture* tex = property.GetSrcObject<FbxFileTexture>(0);
					szFileName = tex->GetFileName();
				}
			}
		}
	}pObject->m_szTextureName = I_Tex.GetSplitName(szFileName);

	int iNumPolyCount = pFbxMesh->GetPolygonCount();
	// 3 정점 -> 1폴리곤( 삼각형)
	// 4 정점 -> 1폴리곤( 쿼드 )
	int iNumFace = 0;

	// 제어점
	FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
	for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
	{
		int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
		iNumFace = iPolySize - 2;
		for (int iFace = 0; iFace < iNumFace; iFace++)
		{
			//정점 인덱스
			int iCornerIndex[3];
			iCornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, 0);
			iCornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 2);
			iCornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 1);

			int iUvIndex[3];
			iUvIndex[0] = pFbxMesh->GetTextureUVIndex(iPoly, 0);
			iUvIndex[1] = pFbxMesh->GetTextureUVIndex(iPoly, iFace+2);
			iUvIndex[2] = pFbxMesh->GetTextureUVIndex(iPoly, iFace+1);

			for (int iIndex = 0; iIndex < 3; iIndex++)
			{
				int vertexID = iCornerIndex[iIndex];
				FbxVector4 v = pVertexPositions[vertexID];
				SimpleVertex tVertex;
				tVertex.p.x = v.mData[0];
				tVertex.p.y = v.mData[2];
				tVertex.p.z = v.mData[1];
				tVertex.c = { 1,1,1,1 };
				FbxVector2 t = ReadTextureCoord(pFbxMesh, pUVSet,
								iCornerIndex[iIndex],
								iUvIndex[iIndex]);
				tVertex.t.x = t.mData[0];
				tVertex.t.y = 1.0f - t.mData[1];

				pObject->m_VertexList.push_back(tVertex);
			}
		}
	}

	m_pDrawObjList.push_back(pObject);
}
FbxVector2 KFbxLoader::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet,int vertexIndex,int uvIndex)
{
	/*
	enum EMappingMode
	{
	eNode, //매핑이 결정되지 않았다
	eBycontrolPoint, //제어점 및 정점에 1개의 매핑이 되어있다
	eByPolygonVertex, //각 정점이 속한 폴리곤의 매핑에 좌표가 있다
	eByPolygon, // 전체 폴리곤에 매핑 좌표가 있다.
	eByEdge, // 에지에 1개의 매핑좌표가 있다.
	eAllSame // 전체 폴리곤에 1개의 매핑 좌표가 있다.
	}
	*/
	/*
	enum EReferenceMode
	{
		eDirect, // n번째 매핑 정보가 mDirectArray의 n번째 위치에 있다.
		eIndex, // fbx 5.0이하의 버전에서 사용되었었다 이상 버전에서는 eIndexToDirect로 대체되었다.
		eIndexToDirect
	}
	텍스처 매핑 방식이 뭐냐
	*/
	FbxVector2 t;
	FbxLayerElement::EMappingMode mode = pUVSet->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (pUVSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			t = pUVSet->GetDirectArray().GetAt(vertexIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = pUVSet->GetIndexArray().GetAt(vertexIndex);
			t = pUVSet->GetDirectArray().GetAt(index);
		}break;
		}break;
	}break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (pUVSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		case FbxLayerElement::eIndexToDirect:
		{
			t = pUVSet->GetDirectArray().GetAt(uvIndex);
		}break;
		}break;
	}break;
	}

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

	if (m_pFbxScene != nullptr)
	{
		m_pFbxScene->Destroy();
		m_pFbxScene = nullptr;
	}
	if (m_pFbxImporter != nullptr)
	{
		m_pFbxImporter->Destroy();
		m_pFbxImporter = nullptr;
	}
	if (m_pFbxManager != nullptr)
	{
		m_pFbxManager->Destroy();
		m_pFbxManager = nullptr;
	}
	return true;
}