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

	void OnKeyPress(BYTE _key);

private:
	float m_Speed;
};

