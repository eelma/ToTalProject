#include"KFbxFile.h"

bool KFbxFile::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
	return true;
}
bool KFbxFile::Load(C_STR filename)
{

	m_pFbxImporter->Initialize(filename.c_str());
	m_pFbxImporter->Import(m_pFbxScene);

	FbxAxisSystem SceneAxisSystem = m_pFbxScene->GetGlobalSettings().GetAxisSystem();
	//����
	FbxSystemUnit::m.ConvertScene(m_pFbxScene);
	//���� ���
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);
	//FbxGeometryConverter converter(m_pFbxManager);
	//converter.Triangulate(m_pFbxScene, true);
	InitAnimation();
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode);

	for (auto kObj : m_pObjectList)
	{
		if (kObj->m_pFbxParentNode != nullptr)
		{
			auto data = m_pObjectMap.find(kObj->m_pFbxParentNode);
			kObj->SetParent(data->second);
		}
		FbxMesh* pFbxMesh = kObj->m_pFbxNode->GetMesh();
		if (pFbxMesh)
		{
			ParseMesh(pFbxMesh, kObj);
		}
	}
	//animation
	FbxTime time;
	for (FbxLongLong t = m_AnimScene.iStartFrame; t <= m_AnimScene.iEndFrame; t++)
	{
		time.SetFrame(t, m_AnimScene.TimeMode);
		LoadAnimation(t, time);
	}
	return true;
}
void KFbxFile::ParseMesh(FbxMesh* pFbxMesh, KFbxObjectSkinning* pObject)
{
	//��Ű�� ���� Ȯ��
	pObject->m_bSkinned = ParseMeshSkinning(pFbxMesh, pObject);

	FbxNode* pNode = pFbxMesh->GetNode();
	FbxAMatrix geom;//����(��Į)���(�ʱ� ���� ��ġ�� ��ȯ�� �� ����ѵ�)
	FbxVector4 trans = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 rot = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	geom.SetT(trans);
	geom.SetR(rot);
	geom.SetS(scale);
	FbxAMatrix normalLocalMatrix = geom;
	normalLocalMatrix = normalLocalMatrix.Inverse();
	normalLocalMatrix = normalLocalMatrix.Transpose();

	//FbxAMatrix matWorldTransform= pObject->m_fbxLocalMatrix;
	////// ����������� = �ڱ�(���ϸ��̼�) ��� * �θ�((���ϸ��̼�))���
	////if (pObject->m_pParent)
	////{
	////	matWorldTransform = 
	////		pObject->m_pParent->m_fbxLocalMatrix * 
	////		pObject->m_fbxLocalMatrix;
	////}		
	//FbxAMatrix normalWorldMatrix = matWorldTransform;
	//normalWorldMatrix = normalWorldMatrix.Inverse();
	//normalWorldMatrix = normalWorldMatrix.Transpose();

	// Layer ����
	FbxLayerElementUV* VertexUvSet = nullptr;
	FbxLayerElementVertexColor* VertexColorSet = nullptr;
	FbxLayerElementNormal* VertexNormalSet = nullptr;
	FbxLayerElementMaterial* MaterialSet = nullptr;
	FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);
	if (pFbxLayer->GetUVs() != nullptr)
	{
		VertexUvSet = pFbxLayer->GetUVs();
	}
	if (pFbxLayer->GetVertexColors() != nullptr)
	{
		VertexColorSet = pFbxLayer->GetVertexColors();
	}
	if (pFbxLayer->GetNormals() != nullptr)
	{
		VertexNormalSet = pFbxLayer->GetNormals();
	}
	if (pFbxLayer->GetMaterials() != nullptr)
	{
		MaterialSet = pFbxLayer->GetMaterials();
	}

}