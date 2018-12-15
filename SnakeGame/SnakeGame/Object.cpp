#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
	: m_Shape(L' ') // wchar_t로 바뀌었으므로, L' '로 해줘야 한다.
	, m_X(0)
	, m_Y(0)
	, m_IsRight(false)
	, m_IsBottom(false)
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
	/// > 제가 srand()에 대한 설명이 부족했었네요.
	/// > srand()는 rand()사용할 때마다 호출하는 것이 아니라
	/// > 게임 시작시 딱 한번만 호출되어야 합니다. (GameManager::Init()에서)
	/// > srand()가 매번 호출되면 그 때마다 랜덤시드(랜덤값의 기반)이 갱신되어서
	/// > 모든 rand()가 동일한 랜덤값을 반환하게 되어버립니다.
	/// > srand()는 rand()함수가 값을 산출할 때 참고하는 어떤 기반값을 설정하는 함수입니다.
	//srand((unsigned int)time(nullptr));

	if (m_IsRight)
	{
		++m_X;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
		}
	}
	else
	{
		--m_X;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;
		}
	}
	if (m_IsBottom)
	{
		++m_Y;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
		}
	}
	else
	{
		--m_Y;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
		}
	}
}

void Object::Render()
{
	// 현재 내 위치(m_X, m_Y)에 내 모습(m_Shape)을 그리도록 한다.
	Console::GetInstance().Print(m_Shape, m_X, m_Y);
}
