#pragma once
#include"KGameCore.h"
#include"KCameraDebug.h"
#include"KFbxFile.h"
class Sample:public KGameCore
{
	//KFbxFile m_FBXLoader;
	vector<KFbxFile*> m_fbxList;
	KCameraDebug* m_pMainCamera;

public:
	bool	Init()override;
	bool	Frame()override;
	bool	Render()override;
	bool	Release()override;
	void	ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
};

