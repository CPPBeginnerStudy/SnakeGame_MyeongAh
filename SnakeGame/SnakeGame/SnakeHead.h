#pragma once
#include "Object.h"
#include "Console.h"

class SnakeHead : public Object
{
public:
	SnakeHead();
	virtual ~SnakeHead();

	virtual void Update() override;
	virtual void Render() override;

public:
	float GetSpeed() const { return m_Speed; }
	void SetSpeed(float _speed) { m_Speed = _speed; }
	float GetCurDir() const { return m_CurDir; }
	void SetCurDir(Direction _curDir) { m_CurDir = _curDir; }

	void OnKeyPress(BYTE _key);

private:
	float m_Speed;
	Direction m_CurDir;
};

