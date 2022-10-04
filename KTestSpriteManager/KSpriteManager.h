#pragma once
#include "KSprite.h"

class KSpriteManager : public KSingleTone<KSpriteManager>
{
public:
	vector<W_STR> m_rtNameList;
	vector<RECT_ARRAY> m_rtSpriteList;
	vector<KSprite*> m_pSpriteList;
public:
	ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
private:
	friend class KSingleTone<KSpriteManager>;
	map<wstring, KSprite*> m_List;
	vector<W_STR>  filelist;
public:
	bool GameDataLoad(const TCHAR* pszLoad);
	bool Load(wstring name);
	KSprite* Find(wstring name);
	bool	  Release();
	KSprite& Get(W_STR name);
	KSprite* GetPtr(W_STR name);
private:
	KSpriteManager();
public:
	~KSpriteManager();
};

#define I_Sprite KSpriteManager::GetInstance()

