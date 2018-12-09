#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
	: m_Shape(' ')
	, m_X(0)
	, m_Y(0)
	, m_IsRight(true)
	, m_IsBottom(false)
	, m_VelocityX(1)
	, m_VelocityY(1)
	, m_VelFlagX(false)
	, m_VelFlagY(false)
{
}

Object::~Object()
{
}

void Object::Init()
{
}

void Object::Release()
{
}

void Object::Update()
{
	// 화면의 바운더리를 벗어나려 하면, 반대 방향으로 전환하여 계속 움직이도록 한다.
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	if (m_IsRight)
	{
		m_X += m_VelocityX;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
			m_VelFlagX = true;
		}
	}
	else
	{
		m_X -= m_VelocityX;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;
			m_VelFlagX = true;
		}
	}
	if (m_VelFlagX)
	{
		// 랜덤값 사용을 위해 랜덤시드를 초기화
		srand((unsigned int)time(nullptr));

		m_VelocityX = (rand() % 3) + 1;
		m_VelFlagX = false;
	}

	if (m_IsBottom)
	{
		m_Y += m_VelocityY;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
			m_VelFlagY = true;
		}
	}
	else
	{
		m_Y -= m_VelocityY;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
			m_VelFlagY = true;
		}
	}
	if (m_VelFlagY)
	{
		// 랜덤값 사용을 위해 랜덤시드를 초기화
		srand((unsigned int)time(nullptr));

		m_VelocityY = (rand() % 3) + 1;
		m_VelFlagY = false;
	}
}

void Object::Render()
{
	// 현재 내 위치(m_X, m_Y)에 내 모습(m_Shape)을 그리도록 한다.
	Console::GetInstance().Print(m_Shape, m_X, m_Y);
}
