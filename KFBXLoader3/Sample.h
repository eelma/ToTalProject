#pragma once
#include"KGameCore.h"
#include"KFbxFile.h"
#include"KCameraDebug.h"
#include"KCharacter.h"
class Sample:public KGameCore
{

	vector<KFbxFile*>m_fbxList;
	vector<KCharacter*>m_NpcList;
	KCharacter* m_UserCharacter;
	KCameraDebug* m_pMainCamera;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
};

