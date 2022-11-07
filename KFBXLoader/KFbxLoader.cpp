#include "KFbxLoader.h"
//https://dlemrcnd.tistory.com/85?category=525778
//pnct= position, normal, color, texture
bool KFbxLoader::Init()
{
	//매니저 임포터 씬 생성 해제는 그 반대 순서
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
	// 단위
	FbxSystemUnit::cm.ConvertScene(m_pFbxScene);
	// 기저(행렬)
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);
	return true;
}
bool KFbxLoader::Load(C_STR filename)
{
	//
	m_pFbxImporter->Initialize(filename.c_str());//파일명 넘기기
	m_pFbxImporter->Import(m_pFbxScene);//임포트하고 그걸 씬으로 넘기기
	//FbxGeometryConverter converter(m_pFbxManager);
	//converter.Triangulate(m_pFbxScene, true);

	//fbx는 트리 구조로 되어있음
	//재귀 호출로 전 순회 가능, n 트리여서 자식 수를 알아야함
	//n트리: 자식 개수가 n개임
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode);//오브젝트를 찾아옴

	for (auto mesh : m_pFbxMeshList)
	{
		ParseMesh(mesh);//오브젝트를 해석함
	}
	return true;
}
void KFbxLoader::ParseMesh(FbxMesh* pFbxMesh)
{

	FbxNode* pNode = pFbxMesh->GetNode();
	KFbxObject* pObject = new KFbxObject;
	FbxAMatrix geom; // 기하(로칼)행렬(초기 정점 위치를 변환할 때 사용한다.)
	FbxVector4 trans = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);//Geometric transform은 단위행렬 이걸 얻기위한 함수 3개
	FbxVector4 rot = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	geom.SetT(trans);//메트릭스 번역
	geom.SetR(rot);//오일러 회전
	geom.SetS(scale);//메트릭스 스케일 세팅

	FbxAMatrix normalLocalMatrix = geom;
	normalLocalMatrix = normalLocalMatrix.Inverse();//역행렬
	normalLocalMatrix = normalLocalMatrix.Transpose();//전치

	// 월드행렬
	//노드 의 기본 변환, 회전 및 크기 조정( 기본 TRS 속성 )은 FbxNode::LclTranslation , FbxNode::LclRotation 및 FbxNode::LclScaling 속성을 사용하여 액세스합니다.
	FbxVector4 Translation;
	if (pNode->LclTranslation.IsValid())//이 속성에는 노드의 번역 정보가 포함됩니다.isvalid=유효함
		Translation = pNode->LclTranslation.Get();//https://help.autodesk.com/view/FBX/2017/ENU/?guid=__files_GUID_C35D98CB_5148_4B46_82D1_51077D8970EE_htm

	FbxVector4 Rotation;
	if (pNode->LclRotation.IsValid())
		Rotation = pNode->LclRotation.Get();

	FbxVector4 Scale;
	if (pNode->LclScaling.IsValid())
		Scale = pNode->LclScaling.Get();

	FbxAMatrix matWorldTransform(Translation, Rotation, Scale);
	FbxAMatrix normalWorldMatrix = matWorldTransform;
	normalWorldMatrix = normalWorldMatrix.Inverse();//역행렬
	normalWorldMatrix = normalWorldMatrix.Transpose();//전치

	// Layer 개념
	FbxLayerElementUV* VertexUVSet = nullptr;//UV를 지오메트리에 매핑하기 위한 레이어 요소
	FbxLayerElementVertexColor* VertexColorSet = nullptr;//정점 색상을 형상에 매핑하기 위한 레이어 요소
	FbxLayerElementNormal* VertexNormalSet = nullptr;//지오메트리를 노말 매핑하기 위한 레이어 요소
	FbxLayerElementMaterial* MaterialSet = nullptr;//재질(FbxSurfaceMaterial)을 지오메트리에 매핑하기 위한 레이어 요소
	FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);//FbxLayer 클래스는 계층화 메커니즘의 기반을 제공합니다.
	if (pFbxLayer->GetUVs() != nullptr)//Returns this layer's UV description.이 레이어의 UV 서술을 반환합니다.
	{
		VertexUVSet = pFbxLayer->GetUVs();
	}
	if (pFbxLayer->GetUVs() != nullptr)
	{
		VertexColorSet = pFbxLayer->GetVertexColors();
	}
	if (pFbxLayer->GetNormals() != nullptr)//Returns this layer's Normals description .이 레이어의 노말에 대한 서술을 반환합니다
	{
		VertexNormalSet = pFbxLayer->GetNormals();
	}
	if (pFbxLayer->GetMaterials() != nullptr)//이 레이어의 재료 서술을 반환
	{
		MaterialSet = pFbxLayer->GetMaterials();
	}
	string szFileName;
	int iNumMtrl = pNode->GetMaterialCount();
	vector<C_STR> texList;
	texList.resize(iNumMtrl);

	for (int iMtrl = 0; iMtrl < iNumMtrl; iMtrl++)
	{
		FbxSurfaceMaterial* pSurface = pNode->GetMaterial(iMtrl); //이 클래스에는 재료 설정이 포함되어 있습니다.
		if (pSurface)
		{
			auto property = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (property.IsValid())
			{
				const FbxFileTexture* tex = property.GetSrcObject<FbxFileTexture>(0);//이 클래스는 지오메트리 위에 이미지 매핑을 기술합니다.
				szFileName = tex->GetFileName();
				texList[iMtrl] = szFileName;
			}
		}
	}
		if (iNumMtrl == 1)
		{
			pObject->m_szTextureName = I_Tex.GetSplitName(szFileName);
		}
		if (iNumMtrl > 1)
		{
			pObject->vbDataList.resize(iNumMtrl);
			pObject->vbTexList.resize(iNumMtrl);
			for (int iTex = 0; iTex < iNumMtrl; iTex++)
			{
				pObject->vbTexList[iTex] = I_Tex.GetSplitName(texList[iTex]);
			}
		}
	

	int iNumPolyCount = pFbxMesh->GetPolygonCount();
	// 3 정점 -> 1폴리곤( 삼각형)
	// 4 정점 -> 1폴리곤( 쿼드 )
	int iNumFace = 0;
	int iBasePolyIndex = 0;
	int iSubMtrl = 0;
	// 제어점
	FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
	for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
	{
		int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
		iNumFace = iPolySize - 2;
		if (MaterialSet)
		{
			iSubMtrl = GetSubMaterialIndex(iPoly, MaterialSet);
		}
		for (int iFace = 0; iFace < iNumFace; iFace++)
		{
			//정점 컬러 인덱스
			int VertexColor[3] = { 0,iFace + 2,iFace + 1 };
			//정점 인덱스
			int iCornerIndex[3];
			iCornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, 0);
			iCornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 2);
			iCornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 1);

			int iUvIndex[3];
			iUvIndex[0] = pFbxMesh->GetTextureUVIndex(iPoly, 0);
			iUvIndex[1] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 2);
			iUvIndex[2] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 1);

			for (int iIndex = 0; iIndex < 3; iIndex++)
			{
				int vertexID = iCornerIndex[iIndex];
				FbxVector4 v2 = pVertexPositions[vertexID];
				PNCT_VERTEX kVertex;
				FbxVector4 v = geom.MultT(v2);
				v = matWorldTransform.MultT(v);
				kVertex.p.x = v.mData[0];
				kVertex.p.y = v.mData[2];
				kVertex.p.z = v.mData[1];
				kVertex.c = { 1,1,1,1 };
				if (VertexColorSet)
				{
					FbxColor c = ReadColor(
						pFbxMesh,
						VertexColorSet,
						iCornerIndex[iIndex],
						iBasePolyIndex + VertexColor[iIndex]);
					kVertex.c.x = c.mRed;
					kVertex.c.y = c.mGreen;
					kVertex.c.z = c.mBlue;
					kVertex.c.w = 1.0f;
				}
				if (VertexUVSet)
				{
					FbxVector2 t = ReadTextureCoord(pFbxMesh, VertexUVSet,
						iCornerIndex[iIndex],
						iUvIndex[iIndex]);
					kVertex.t.x = t.mData[0];
					kVertex.t.y = 1.0f - t.mData[1];
				}
				if (VertexNormalSet)
				{
					FbxVector4 n = ReadNormal(
						pFbxMesh,
						VertexNormalSet,
						iCornerIndex[iIndex],
						iBasePolyIndex + VertexColor[iIndex]);
					n = normalLocalMatrix.MultT(n);
					n = normalWorldMatrix.MultT(n);
					kVertex.n.x = n.mData[0];
					kVertex.n.y = n.mData[2];
					kVertex.n.z = n.mData[1];
				}
				if (iNumMtrl <= 1)
				{
					pObject->m_VertexList.push_back(kVertex);
				}
				else
				{
					pObject->vbDataList[iSubMtrl].push_back(kVertex);
				}
			}
		}iBasePolyIndex += iPolySize;
	}

	m_pDrawObjList.push_back(pObject);
}
FbxVector2 KFbxLoader::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* VertexUVSet,int vertexIndex,int uvIndex)
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
	FbxLayerElement::EMappingMode mode = VertexUVSet->GetMappingMode();//매핑모드를 반환
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint://1
	{
		switch (VertexUVSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect://0
		{
			t = VertexUVSet->GetDirectArray().GetAt(vertexIndex);//레이어 요소의 직접 배열을 반환합니다. 지정된 항목의 값을 반환(vertexIndex)
		}break;
		case FbxLayerElementUV::eIndexToDirect://2
		{
			int index = VertexUVSet->GetIndexArray().GetAt(vertexIndex);
			t = VertexUVSet->GetDirectArray().GetAt(index);
		}break;
		}break;
	}break;
	case FbxLayerElementUV::eByPolygonVertex://2
	{
		switch (VertexUVSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect://0
		case FbxLayerElement::eIndexToDirect://2
		{
			t = VertexUVSet->GetDirectArray().GetAt(uvIndex);//
		}break;
		}break;
	}break;
	}

	return t;
}

void KFbxLoader::PreProcess(FbxNode* pFbxNode)
{
	if (pFbxNode == nullptr) return;
	FbxMesh* pFbxMesh = pFbxNode->GetMesh();//노드의 매쉬를 만듬, 버텍스 pnct를 채워줘야함
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
FbxColor KFbxLoader::ReadColor(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* VertexColorSet, int posIndex, int colorIndex)
{
	FbxColor color(1, 1, 1, 1);
	FbxLayerElement::EMappingMode mode = VertexColorSet->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (VertexColorSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			color = VertexColorSet->GetDirectArray().GetAt(posIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = VertexColorSet->GetIndexArray().GetAt(posIndex);
			color = VertexColorSet->GetDirectArray().GetAt(index);
		}break;
		}break;
	}break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (VertexColorSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			color = VertexColorSet->GetDirectArray().GetAt(colorIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = VertexColorSet->GetIndexArray().GetAt(colorIndex);
			color = VertexColorSet->GetDirectArray().GetAt(index);
		}break;
		}break;
	}break;
	}
	return color;
}
int KFbxLoader::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList)
{
	int iSubMtrl = 0;
	if (pMaterialSetList != nullptr)
	{
		switch (pMaterialSetList->GetMappingMode())
		{
		case FbxLayerElement::eByPolygon:
		{

			switch (pMaterialSetList->GetReferenceMode())
			{
			case FbxLayerElement::eIndex:
			{
				iSubMtrl = iPoly;
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				iSubMtrl = pMaterialSetList->GetIndexArray().GetAt(iPoly);
			}break;
			}
		}
		default:
		{
			break;
		}
		}
	}
	return iSubMtrl;
}

FbxVector4 KFbxLoader::ReadNormal(FbxMesh* pFbxMesh, FbxLayerElementNormal* VertexNormalSet, int posIndex, int colorIndex)
{
	FbxVector4 normal(1, 1, 1, 1);
	FbxLayerElement::EMappingMode mode = VertexNormalSet->GetMappingMode();
	switch(mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (VertexNormalSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			normal = VertexNormalSet->GetDirectArray().GetAt(posIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = VertexNormalSet->GetIndexArray().GetAt(posIndex);
			normal = VertexNormalSet->GetDirectArray().GetAt(index);
		}break;
		}break;
	}break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (VertexNormalSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			normal = VertexNormalSet->GetDirectArray().GetAt(colorIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = VertexNormalSet->GetIndexArray().GetAt(colorIndex);
			normal = VertexNormalSet->GetDirectArray().GetAt(index);
		}break;
		}break;
	}break;
	}
	return normal;
}
