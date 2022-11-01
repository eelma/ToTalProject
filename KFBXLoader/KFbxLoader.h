#pragma once
#include"KStd.h"
#include"fbxsdk.h"
#include"KObject3D.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")
class KFbxObject : public KBaseObject
{
public:
	void  CreateVertexData()
	{
	}
	HRESULT CreateIndexBuffer()
	{
		return S_OK;
	}
};
class KFbxLoader
{
public:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	FbxNode* m_pRootNode;
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
	void ParseMesh(FbxMesh* pFbxMesh);
	FbxVector2 ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet,
		int posIndex, int uvIndex);
};