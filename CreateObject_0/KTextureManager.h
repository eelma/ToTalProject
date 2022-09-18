#pragma once
#include"KTexture.h"
class KTextureManager:public KSingleTone<KTextureManager>
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	void SetDevice(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext);
	private:
	friend KSingleTone<KTextureManager>;
	map<wstring, KTexture*>m_List;
public:
	KTexture* Load(wstring name);
	bool Release();
private:
	KTextureManager();
	~KTextureManager();

};

#define I_Tex KTextureManager::GetInstance()