#pragma once
#include "KFiniteState.h"
using namespace std;
class KFsm
{
private:
	//       ����(����), �ش� Ŭ����
	std::map<DWORD, KFiniteState*> m_State;
public:
	void  AddTransition(DWORD inState, 
						DWORD event, 
						DWORD outState);
	DWORD GetTransition(DWORD dwState,
						DWORD dwEvent);

	~KFsm();
};

