#pragma once
#include"KGameCore.h"
#include"KCameraDebug.h"
#include"KFbxLoader.h"
class Sample:public KGameCore
{
	KFbxLoader m_FBXLoader;
	KCameraDebug* m_pMainCamera;
	KBaseObject m_BG2;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;

};

