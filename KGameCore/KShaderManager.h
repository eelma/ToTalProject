#pragma once
#include"KShader.h"
class KShaderManager:public KSingleTone<KShaderManager>
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	void SetDevice(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext);

	private:
	friend KSingleTone<KShaderManager>;
	map<wstring, KShader*>m_List;//매니저에서 원하는 쉐이더 이름을 Kshader로 map으로 관리하겠다

public:
	KShader* Load(wstring name);
	KShader* VLoad(wstring name, string funName = "VS");
	KShader* PLoad(wstring name, string funName = "PS");

	bool Release();

private:
	KShaderManager();
	~KShaderManager();

};

#define I_Shader KShaderManager::GetInstance()