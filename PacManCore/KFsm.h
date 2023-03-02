#pragma once
#include "KFiniteState.h"
using namespace std;
class KFsm
{
private:
	//       상태(동작), 해당 클래스
	std::map<DWORD, KFiniteState*> m_State;
public:
	void  AddTransition(DWORD inState, 
						DWORD event, 
						DWORD outState);
	DWORD GetTransition(DWORD dwState,
						DWORD dwEvent);

	~KFsm();
};

