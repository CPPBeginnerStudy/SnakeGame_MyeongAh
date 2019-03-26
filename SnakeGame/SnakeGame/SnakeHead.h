#pragma once
#include "Object.h"
#include "Console.h"

class SnakeHead : public Object
{
public:
	SnakeHead();
	virtual ~SnakeHead();

	virtual void Update(float _dt) override;
	virtual void Render() override;

	virtual bool HitCheck(Object* _pOther) override;
	virtual void OnHit(Object* _pHitter) override;

public:
	int	GetSpeed() const { return m_Speed; }
	void	SetSpeed(int _speed) { m_Speed = _speed; }

//	float	GetCurDir() const { return m_CurDir; }
//	void	SetCurDir(Direction _curDir) { m_CurDir = _curDir; }

	void	OnKeyPress(int _key);
	void	AddTail();
	void    ClearTails();

private:
	int					m_Speed;
	Direction			m_CurDir;
	std::list<Object*>	m_TailList;
};

