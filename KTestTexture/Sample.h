#pragma once
#include "KGameCore.h"
#include "KBaseObject.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#ifdef _DEBUG
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DirectXTK_D.lib")
#else
#pragma comment(lib, "DirectXTK_R.lib")
#endif

class Sample : public KGameCore
{
public:
	ID3D11SamplerState* g_pDefaultSS;
	ID3D11Texture2D* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	D3D11_TEXTURE2D_DESC		m_Desc;
	KBaseObject					m_Object;
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};
