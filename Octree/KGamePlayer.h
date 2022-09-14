#pragma once
#include "KObject.h"
template<class T>
class KPlayer
{
protected:
	T* m_pImp;
public:	
	T* GetImp() { return m_pImp; }
	virtual void   SetPosition(KVector p, KVector s) {};
	virtual void   SetPosition(KVector2D p, KVector2D s) {};
	virtual void	Frame(float fDeltaTime, float fGameTime) {};
	virtual void    Render() {};
	virtual ~KPlayer() {}
};
class KGamePlayer : public KPlayer<KObject>
{
public:
	virtual void   SetPosition(KVector p, KVector s) {
		m_pImp->SetPosition(p, s);
	};
	void	Frame(float fDeltaTime, float fGameTime) override;
	void    Render() override;
	KGamePlayer()
	{
		m_pImp = new KObject;
	}
	~KGamePlayer()
	{
		delete m_pImp;
	}
};
class KGamePlayer2D : public KPlayer<KObject2D>
{
public:
	virtual void   SetPosition(KVector2D p, KVector2D s) {
		m_pImp->SetPosition(p, s);
	};
	void	Frame(float fDeltaTime, float fGameTime) override;
	void    Render() override;
	KGamePlayer2D()
	{
		m_pImp = new KObject2D;
	}
	~KGamePlayer2D()
	{
		delete m_pImp;
	}
};
