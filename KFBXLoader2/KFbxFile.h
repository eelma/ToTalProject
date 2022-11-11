#pragma once
#include"KStd.h"
#include<fbxsdk.h>
#include"KFbxObject.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

class KFbxFile
{
public:
	KAnimScene m_AnimScene;
	float m_fAnimFrame = 0;
	float m_fAnimInverse = 1.0f;
	float m_fAnimSpeed = 1.0f;

public:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	FbxNode* m_pRootNode;
	map<FbxNode*, KFbxObjectSkinning*>m_pObjectMap;
	map<FbxNode*, UINT>m_pObjectIDMap;
	vector<KFbxObjectSkinning*>m_pObjectList;


	std::vector< FbxMesh* > m_pFbxMeshList;
	std::vector< KFbxObjectSkinning* > m_pDrawObjList;
	ID3D11DeviceContext* m_pContext = nullptr;

	VS_CONSTANT_BONE_BUFFER m_cbDataBone;
	ID3D11Buffer* m_pConstantBufferBone;
	HRESULT CreateConstantBuffer(ID3D11Device* pDevice);

	//ID3D11Device 인터페이스는 기능 지원 점검과 자원 할당에 쓰인다.
	//ID3D11DeviceContext 인터페이스는 렌더 대상을 설정하고, 자원을 그래픽 파이프 라인에 묶고,
	//GPU가 렌더링 명령들을 지시하는 데 쓰인다.
	
public:
	bool Init();
	bool UpdateFrame(ID3D11DeviceContext* pContext);
	bool Render();
	bool Release();
	bool Load(C_STR filename);
	void PreProcess(FbxNode* pFbxNode);
	void ParseMesh(FbxMesh* pFbxMesh, KFbxObjectSkinning* pObject);
	FbxVector2 ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* VertexUVSet,
		int posIndex, int uvIndex);


	FbxColor ReadColor(FbxMesh* pFbxMesh,
		FbxLayerElementVertexColor* VertexColorSet,
		int posIndex, int colorIndex);
	int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* MaterialSet);
	FbxVector4 ReadNormal(FbxMesh* pFbxMesh,
		FbxLayerElementNormal* VertexNormalSet,
		int posIndex,
		int colorIndex);
	void InitAnimation();
	void LoadAnimation(KFbxObjectSkinning* pObj);
	TMatrix ConvertMatrix(FbxAMatrix& fbxMatrix);
	TMatrix DxConvertMatrix(FbxAMatrix& fbxMatrix);
};