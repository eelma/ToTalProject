#pragma once
#include"KGameCore.h"
#include"KCameraDebug.h"
#include"KFbxLoader.h"
class Sample:public KGameCore
{
	//KFbxLoader m_FBXLoader;
	vector<KFbxLoader*> m_fbxList;
	KCameraDebug* m_pMainCamera;

public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool	Release()override;

};

