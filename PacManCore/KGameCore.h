#pragma once
#include"KDevice.h"
#include"KInput.h"
#include"KTimer.h"
#include"KWriter.h"
#include "KSoundManager.h"
#include"KTextureManager.h"
#include"KShaderManager.h"
class KGameCore:public KDevice
{
public:
	ID3D11SamplerState* m_pDefaultSS=nullptr;

	KWriter m_Writer;
	bool bGameRun = true;
public:
	virtual bool		Init() { return true; }; // 초기화
	virtual bool		Frame() { return true; };// 실시간 계산
	virtual bool		Render() { return true; };// 실시간 랜더링
	virtual bool		Release() { return true; };// 소멸 및 삭제

	//프로젝트에서 건들지 말라고 프라이빗으로 묶어둠 정보은닉
private:
	bool		KCoreInit(); // 초기화
	bool		KCoreFrame();// 실시간 계산
	bool		KCoreRender();// 실시간 랜더링
	bool		KCorePreRender();
	bool		KCorePostRender();
	bool		KCoreRelease();// 소멸 및 삭제	
public:
	bool		Run()override; // 소멸 및 삭제	

};

