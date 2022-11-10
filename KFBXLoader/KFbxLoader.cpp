#include "KFbxLoader.h"
//https://dlemrcnd.tistory.com/85?category=525778
//pnct= position, normal, color, texture
//uv ���� - 3d �𵨸��� ������ �����ִ� ���� ���������� ������� ������Ʈ�� ������ �����ִ� ����
bool KFbxLoader::Init()
{
	//�Ŵ��� ������ �� ���� ������ �� �ݴ� ����
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
	// ����
	FbxSystemUnit::cm.ConvertScene(m_pFbxScene);
	// ����(���)
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);
	return true;
}
bool KFbxLoader::Load(C_STR filename)
{
	//
	m_pFbxImporter->Initialize(filename.c_str());//���ϸ� �ѱ��
	m_pFbxImporter->Import(m_pFbxScene);//����Ʈ�ϰ� �װ� ������ �ѱ��
	//����
	FbxSystemUnit::m.ConvertScene(m_pFbxScene);
	//����(���)
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);
	//FbxGeometryConverter converter(m_pFbxManager);
	//converter.Triangulate(m_pFbxScene, true);

	//fbx�� Ʈ�� ������ �Ǿ�����
	//��� ȣ��� �� ��ȸ ����, n Ʈ������ �ڽ� ���� �˾ƾ���
	//nƮ��: �ڽ� ������ n����
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode);//������Ʈ�� ã�ƿ�

	for (auto tObj : m_pObjectList)
	{
		if (tObj->m_pFbxParentNode != nullptr)
		{
			auto data = m_pObjectMap.find(tObj->m_pFbxParentNode);
			tObj->SetParent(data->second);
		}
		LoadAnimation(tObj);
		FbxMesh* pFbxMesh = tObj->m_pFbxNode->GetMesh();
		if (pFbxMesh)
		{
			m_pFbxMeshList.push_back(pFbxMesh);
			ParseMesh(pFbxMesh, tObj);
		}
	}
	return true;
}
void KFbxLoader::ParseMesh(FbxMesh* pFbxMesh, KFbxObject* pObject)
{

	FbxNode* pNode = pFbxMesh->GetNode();
	//�������(FBX ��ġ ���ؽ����� ->�ʱ� ���� ���� ��ġ�� ��ȯ)
	FbxAMatrix geom; // ����(��Į)���(�ʱ� ���� ��ġ�� ��ȯ�� �� ����Ѵ�.)
	FbxVector4 trans = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);//Geometric transform�� ������� �̰� ������� �Լ� 3��
	FbxVector4 rot = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	geom.SetT(trans);//��Ʈ���� ����
	geom.SetR(rot);//���Ϸ� ȸ��
	geom.SetS(scale);//��Ʈ���� ������ ����

	//�븻 ����� ��������� ������� ��ġ
	//�븻 ��Ʈ����
	FbxAMatrix normalLocalMatrix = geom;
	normalLocalMatrix = normalLocalMatrix.Inverse();//�����
	normalLocalMatrix = normalLocalMatrix.Transpose();//��ġ

	FbxAMatrix matWorldTransform = pObject->m_fbxLocalMatrix;
	//�����������=�ڱ�(�ִϸ��̼�)���*�θ�((�ִϸ��̼�))���
	//if(pObject->m_pParent)
	//{
	//matWorldTransform=
	//pObject->m_pParent->m_fbxLocalMatrix*
	//pObject->m_fbxLocalMatrix;
	//}
	//FbxAMatrixNomalWolrdMatrix=matWorldTransform;
	//normalWorldMatrix=normalWorldMatrix.Inverse();
	//normalWorldMatrix=normalWorldMatrix.Transpose();

	// �������
	//��� �� �⺻ ��ȯ, ȸ�� �� ũ�� ����( �⺻ TRS �Ӽ� )�� FbxNode::LclTranslation , FbxNode::LclRotation �� FbxNode::LclScaling �Ӽ��� ����Ͽ� �׼����մϴ�.
	//FbxVector4 Translation;
	//if (pNode->LclTranslation.IsValid())//�� �Ӽ����� ����� ���� ������ ���Ե˴ϴ�.isvalid=��ȿ��
	//	Translation = pNode->LclTranslation.Get();//https://help.autodesk.com/view/FBX/2017/ENU/?guid=__files_GUID_C35D98CB_5148_4B46_82D1_51077D8970EE_htm

	//FbxVector4 Rotation;
	//if (pNode->LclRotation.IsValid())
	//	Rotation = pNode->LclRotation.Get();

	//FbxVector4 Scale;
	//if (pNode->LclScaling.IsValid())
	//	Scale = pNode->LclScaling.Get();

	//FbxAMatrix matWorldTransform(Translation, Rotation, Scale);
	//FbxAMatrix normalWorldMatrix = matWorldTransform;
	//normalWorldMatrix = normalWorldMatrix.Inverse();//�����
	//normalWorldMatrix = normalWorldMatrix.Transpose();//��ġ

	// Layer ����
	FbxLayerElementUV* VertexUVSet = nullptr;//UV�� ������Ʈ���� �����ϱ� ���� ���̾� ���
	FbxLayerElementVertexColor* VertexColorSet = nullptr;//���� ������ ���� �����ϱ� ���� ���̾� ���
	FbxLayerElementMaterial* MaterialSet = nullptr;//����(FbxSurfaceMaterial)�� ������Ʈ���� �����ϱ� ���� ���̾� ��� ���͸���

	FbxLayerElementNormal* VertexNormalSet = nullptr;//������Ʈ���� �븻 �����ϱ� ���� ���̾� ���
	FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);//FbxLayer Ŭ������ ����ȭ ��Ŀ������ ����� �����մϴ�.
	if (pFbxLayer->GetUVs() != nullptr)//Returns this layer's UV description.�� ���̾��� UV ������ ��ȯ�մϴ�.
	{
		VertexUVSet = pFbxLayer->GetUVs();
	}
	if (pFbxLayer->GetVertexColors() != nullptr)
	{
		VertexColorSet = pFbxLayer->GetVertexColors();
	}
	if (pFbxLayer->GetNormals() != nullptr)//Returns this layer's Normals description .�� ���̾��� �븻�� ���� ������ ��ȯ�մϴ�
	{
		VertexNormalSet = pFbxLayer->GetNormals();
	}
	if (pFbxLayer->GetMaterials() != nullptr)//�� ���̾��� ��� ������ ��ȯ
	{
		MaterialSet = pFbxLayer->GetMaterials();
	}
	string szFileName;
	//���͸��� ���� ��ŭ ���鼭 �о��
	int iNumMtrl = pNode->GetMaterialCount();
	vector<C_STR> texFullNameList;
	texFullNameList.resize(iNumMtrl);

	for (int iMtrl = 0; iMtrl < iNumMtrl; iMtrl++)
	{
		FbxSurfaceMaterial* pSurface = pNode->GetMaterial(iMtrl); //�� Ŭ�������� ��� ������ ���ԵǾ� �ֽ��ϴ�.
		if (pSurface)
		{
			auto property = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (property.IsValid())
			{
				const FbxFileTexture* tex = property.GetSrcObject<FbxFileTexture>(0);//�� Ŭ������ ������Ʈ�� ���� �̹��� ������ ����մϴ�.
				if(tex)
				{
				szFileName = tex->GetFileName();
				texFullNameList[iMtrl] = szFileName;
				}
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
				pObject->vbTexList[iTex] = I_Tex.GetSplitName(texFullNameList[iTex]);
			}
		}
	

	int iNumPolyCount = pFbxMesh->GetPolygonCount();//������ ��
	// 3 ���� -> 1������( �ﰢ��)
	// 4 ���� -> 1������( ���� )
	int iNumFace = 0;
	int iBasePolyIndex = 0;
	int iSubMtrl = 0;
	// ������
	FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();//���� ��ġ
	for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
	{
		int iPolySize = pFbxMesh->GetPolygonSize(iPoly);//4 �Ǵ� 3 �ﰢ���̳� �簢���̳�
		iNumFace = iPolySize - 2;//�Ѹ� ���ϴ� ���
		if (MaterialSet)
		{
			iSubMtrl = GetSubMaterialIndex(iPoly, MaterialSet);
		}
		//�� 4-2�� 2���� Ʈ���̾ޱ�
		for (int iFace = 0; iFace < iNumFace; iFace++)
		{
			//���� �÷� �ε���
			int VertexColor[3] = { 0,iFace + 2,iFace + 1 };
			//���� �ε���
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
				FbxVector4 v = geom.MultT(v2);//���� ��ǥ�� ��� ��
				//v = pObject->m_AnimTracks[30].fbxMatrix.MulT(v);
				kVertex.p.x = v.mData[0];
				kVertex.p.y = v.mData[2];
				kVertex.p.z = v.mData[1];
				kVertex.c = { 1,1,1,1 };
				//���� ���ؽ� Į�� ���� �ִٸ�
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
					kVertex.c.w = 1.0f;//���ؽ� �÷����� ����
				}
				//uv ����Ʈ�� ���� �ִٸ�
				if (VertexUVSet)
				{
					FbxVector2 t = ReadTextureCoord(pFbxMesh, VertexUVSet,
						iCornerIndex[iIndex],
						iUvIndex[iIndex]);
					kVertex.t.x = t.mData[0];
					kVertex.t.y = 1.0f - t.mData[1];
				}
				//��ְ��� �ִٸ�
				if (VertexNormalSet)
				{
					FbxVector4 n = ReadNormal(
						pFbxMesh,
						VertexNormalSet,
						iCornerIndex[iIndex],
						iBasePolyIndex + VertexColor[iIndex]);
					n = normalLocalMatrix.MultT(n);
					
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
	eNode, //������ �������� �ʾҴ�
	eBycontrolPoint, //������ �� ������ 1���� ������ �Ǿ��ִ�
	eByPolygonVertex, //�� ������ ���� �������� ���ο� ��ǥ�� �ִ�
	eByPolygon, // ��ü �����￡ ���� ��ǥ�� �ִ�.
	eByEdge, // ������ 1���� ������ǥ�� �ִ�.
	eAllSame // ��ü �����￡ 1���� ���� ��ǥ�� �ִ�.
	}
	*/
	/*
	enum EReferenceMode
	{
		eDirect, // n��° ���� ������ mDirectArray�� n��° ��ġ�� �ִ�.
		eIndex, // fbx 5.0������ �������� ���Ǿ����� �̻� ���������� eIndexToDirect�� ��ü�Ǿ���.
		eIndexToDirect
	}
	�ؽ�ó ���� ����� ����
	*/
	FbxVector2 t;
	FbxLayerElement::EMappingMode mode = VertexUVSet->GetMappingMode();//���θ�带 ��ȯ
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint://1
	{
		switch (VertexUVSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect://0
		{
			t = VertexUVSet->GetDirectArray().GetAt(vertexIndex);//���̾� ����� ���� �迭�� ��ȯ�մϴ�. ������ �׸��� ���� ��ȯ(vertexIndex)
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

void KFbxLoader::PreProcess(FbxNode* pFbxNode)//��ó������
{
	if (pFbxNode && (pFbxNode->GetCamera() || pFbxNode->GetLight()))
	{
		return;
	}
	KFbxObject* pObject = new KFbxObject;
	string name = pFbxNode->GetName();
	pObject->m_szName = to_mw(name);
	pObject->m_pFbxNode = pFbxNode;
	pObject->m_pFbxParentNode = pFbxNode->GetParent();

	m_pObjectList.push_back(pObject);
	m_pObjectMap.insert(make_pair(pFbxNode, pObject));


	int iNumChild = pFbxNode->GetChildCount();
	for (int iChild = 0; iChild < iNumChild; iChild++)
	{
		FbxNode* pChild = pFbxNode->GetChild(iChild);
		//���ۿ�����Ʈ+������Ʈ�� ������Ʈ
		FbxNodeAttribute::EType type = pChild->GetNodeAttribute()->GetAttributeType();
		if (type == FbxNodeAttribute::eMesh ||
			type == FbxNodeAttribute::eSkeleton ||
			type == FbxNodeAttribute::eNull)
		{
			PreProcess(pChild);
		};
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
void KFbxLoader::LoadAnimation(KFbxObject* pObj)
{
	FbxNode* pNode = pObj->m_pFbxNode;
	FbxAnimStack* stackAnim = m_pFbxScene->GetSrcObject<FbxAnimStack>(0);
	FbxLongLong s = 0;
	FbxLongLong n = 0;
	FbxTime::EMode TimeMode;
	if (stackAnim)
	{
		FbxString takeName = stackAnim->GetName();
		FbxTakeInfo* take = m_pFbxScene->GetTakeInfo(takeName);
		FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
		TimeMode = FbxTime::GetGlobalTimeMode();
		FbxTimeSpan localTimeSpan = take->mLocalTimeSpan;
		FbxTime start = localTimeSpan.GetStart();
		FbxTime end = localTimeSpan.GetStop();
		FbxTime Dration = localTimeSpan.GetDirection();
		s = start.GetFrameCount(TimeMode);
		n = end.GetFrameCount(TimeMode);
	}
	pObj->m_AnimScene.iStartFarame = s;
	pObj->m_AnimScene.iEndFrame = n;
	pObj->m_AnimScene.fFrameSpeed = 30.0f;
	pObj->m_AnimScene.fTickPerFrame = 160;
	FbxTime time;
	for (FbxLongLong t = s; t <= n; t++)
	{
		time.SetFrame(t, TimeMode);
		KAnimTrack track;
		track.iFrame = t;
		FbxAMatrix fbxMatrix = pNode->EvaluateGlobalTransform(time);
		//track.fbxMatrix=fbxMatrix;
		track.matAnim = DxConvertMatrix(fbxMatrix);
		D3DXMatrixDecompose(&track.s, &track.r, &track.t, &track.matAnim);
		pObj->m_AnimTracks.push_back(track);
	}
}
TMatrix KFbxLoader::ConvertMatrix(FbxAMatrix& fbxMatrix)
{
	TMatrix mat;
	float* kArray = (float*)(&mat);
	double* fbxArray = (double*)(&fbxMatrix);
	for (int i = 0; i < 16; i++)
	{
		kArray[i] = fbxArray[i];
	}
	return mat;
}
TMatrix KFbxLoader::DxConvertMatrix(FbxAMatrix& fbxMatrix)
{
	TMatrix m = ConvertMatrix(fbxMatrix);
	TMatrix mat;
	mat._11 = m._11; mat._12 = m._13; mat._13 = m._12;
	mat._21 = m._31; mat._22 = m._33; mat._23 = m._32;
	mat._31 = m._21; mat._32 = m._23; mat._33 = m._22;
	mat._41 = m._41; mat._42 = m._43; mat._43 = m._42;
	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._44 = 1.0f;
	return mat;
}