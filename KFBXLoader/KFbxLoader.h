#pragma once
#include"KStd.h"
#include<fbxsdk.h>
#include"KFbxObject.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

class KFbxLoader
{
public:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	FbxNode* m_pRootNode;

	map<FbxNode*, KFbxObject*>m_pObjectMap;
	vector<KFbxObject*>m_pObjectList;


	std::vector< FbxMesh* > m_pFbxMeshList;
	std::vector< KFbxObject* > m_pDrawObjList;
	ID3D11DeviceContext* m_pContext = nullptr;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(C_STR filename);
	void PreProcess(FbxNode* pFbxNode);
	void ParseMesh(FbxMesh* pFbxMesh, KFbxObject* pObject);
	FbxVector2 ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* VertexUVSet,
		int posIndex, int uvIndex);


	FbxColor ReadColor(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* VertexColorSet,
		int posIndex, int colorIndex);
	int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* MaterialSet);
	FbxVector4 ReadNormal(FbxMesh* pFbxMesh,
		FbxLayerElementNormal* VertexNormalSet,
		int posIndex,
		int colorIndex);
	void LoadAnimation(KFbxObject* pObj);
	TMatrix ConvertMatrix(FbxAMatrix& fbxMatrix);
	TMatrix DxConvertMatrix(FbxAMatrix& fbxMatrix);
};