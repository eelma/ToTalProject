#pragma once
#include"KShader.h"
class KShaderManager:public KSingleTone<KShaderManager>
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	void SetDevice(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext);

	private:
	friend KSingleTone<KShaderManager>;
	map<wstring, KShader*>m_List;

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