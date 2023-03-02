#include "KFsm.h"
void  KFsm::AddTransition(DWORD inState,
	DWORD dwEvent,
	DWORD outState)
{
	KFiniteState* pState = nullptr;
	auto ret = m_State.find(inState);
	if (ret != m_State.end())
	{
		pState = ret->second;
	}
	else
	{
		pState = new KFiniteState();
		m_State[inState] = pState;
	}
	pState->AddTransition(dwEvent, outState);
}

DWORD KFsm::GetTransition(	DWORD dwState,
							DWORD dwEvent)
{
	return m_State[dwState]->GetTransition(dwEvent);
}

KFsm::~KFsm()
{
	for (auto list : m_State)
	{
		delete list.second;
	}
	m_State.clear();
}