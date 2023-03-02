#include "KFiniteState.h"
void  KFiniteState::AddTransition(DWORD dwEvent, DWORD outState)
{
	m_State[dwEvent] = outState;
}