#pragma once
#include "KGameCore.h"
#include "KBaseObject.h"
#include "KTextureManager.h"
#include"KShaderManager.h"

class KObject2D : public KBaseObject
{
	KShader* m_pShader = nullptr;
public:

	virtual HRESULT CreateVertexShader(wstring filename);
	virtual HRESULT CreatePixelShader(wstring filename);
};

class Sample : public KGameCore
{
public:
	ID3D11SamplerState* g_pDefaultSS;
	std::vector<KBaseObject*>	m_ObjectList;
	std::vector<KTexture*>		m_ObjectTextureList;
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};

