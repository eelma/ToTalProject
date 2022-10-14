#include "Sample.h"

class KTest
{
public:
	using xText = shared_ptr<KTest>;
	int k;
public:
	KTest()
	{
		k = 10;
	}
	~KTest()
	{
		k = 0;
	}
};
void Function(KTest::xText data)
{
	data.get()->k = 20;
}
void Function(unique_ptr<KTest> data)
{
	data.get()->k = 20;
}



bool Sample::Init()
{
	{
	KTest::xText nullText = nullptr;
	KTest::xText pTitleShared = make_shared<KTest>();
		{
			KTest* pData = pTitleShared.get();
			Function(pTitleShared);
		}
	}

	{
	/*unique_ptr<KTest> pTitle = make_unique<KTest>;
	{
		KTest* pData = pTitle.get();
	}*/
	}

	m_pTitle = make_shared<KSceneTitle>();
	m_pInGame = make_shared<KSceneInGame>();
	
	m_pTitle->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"");
	m_pInGame->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"");
	m_pTitle->Init();
	m_pInGame->Init();
	m_pCurrentScene = m_pTitle;

	return true;
}
bool Sample::Frame()
{
	if (m_pCurrentScene->IsNextScene())
	{
		m_pCurrentScene = m_pInGame;
	}
	m_pCurrentScene->Frame();
	return true;
}
bool Sample::Render()
{
	
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		m_pImmediateContext->RSSetState(KDxState::g_pDefaultRSWireFrame);
	}
	
	m_pCurrentScene->Render();
	return true;
}
bool Sample::Release()
{
	m_pTitle->Release();
	m_pInGame->Release();

	
	return true;
}

GAME_RUN(KSampleTexture, 800, 600)