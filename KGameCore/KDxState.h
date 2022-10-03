#pragma once
#include"KStd.h"
//샘플러 스테이트
class KDxState
{
public:
	static ID3D11SamplerState*	g_pDefaultSSWrap;
	static ID3D11SamplerState*	g_pDefaultSSMirror;
	static ID3D11BlendState*	g_pDefaultBS;
	static ID3D11RasterizerState* g_pDefaultRsWireFrame;
	static ID3D11RasterizerState* g_pDefaultRSSolid;

	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};

