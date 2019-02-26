#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
	: m_Shape(L' ') // wchar_t로 바뀌었으므로, L' '로 해줘야 한다.
	, m_X(0.f)
	, m_Y(0.f)
{
}

Object::~Object()
{
}

void Object::Update()
{
	// 중복 코드라서 이건 함수로 빠진다!
	/*
	if (m_IsRight)
	{
		m_X += 2.f;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
		}
	}
	else
	{
		m_X -= 2.f;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;
		}
	}
	if (m_IsBottom)
	{
		m_Y += 1.f;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
		}
	}
	else
	{
		m_Y -= 1.f;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
		}
	}
	*/
}

void Object::Render()
{
	// 현재 내 위치(m_X, m_Y)에 내 모습(m_Shape)을 그리도록 한다.
	// 실수형 변수로 바꾸어 주었지만, 어차피 도트 겜이라 좌표는 실수가 나올 수 없어서
	// 적당히 short로 형변환 해서 Print에 넣어준다. (print가 받는 인자도 실수형이 아님)
	// m_X를 2배 하는 이유는 cmd에서 X좌표 길이가 Y좌표 길이의 절반이기 때문! 
	Console::GetInstance().Print(m_Shape, (short)(m_X * 2), (short)m_Y);
}

bool Object::Move(Direction _dir, float _distance)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	// cmd 좌표계인 boundaryBox를 인게임 좌표계로 변환하여 계산하도록 한다.
	// cmd 좌표계에서는 X 길이가 Y 길이의 절반이기 때문에 인게임 좌표계산 과정에 바로 쓰기에 부적절하다.
	float minX = (float) boundaryBox.left / 2;
	float maxX = (float) boundaryBox.right / 2;
	float minY = (float) boundaryBox.top;
	float maxY = (float) boundaryBox.bottom;

	switch (_dir)
	{
	case Direction::UP:
		{
			// 현재 y좌표가 위쪽 경계선 보다 크면(아래쪽이면) 위로 이동이 가능
			if (m_Y > minY)
			{
				// 요청한 거리만큼 이동을 시도하며, 바운더리를 넘어서지 않도록 처리한다.
				// std::max는 두 개의 인자 중 더 큰 것을 반환하는 함수이다.
				// m_Y - _distance가 바운더리보다 작으면 바운더리 값을 반환하여, 그 이하 값이 나오지 않도록 한다.
				m_Y = std::max<float>(m_Y - _distance, minY);

				//여기에 왔다는 것은 이동은 하고 있다는 뜻이다.
				return true;
			}
		}
		break;

	case Direction::DOWN:
		{
			// 현재 y좌표가 아래쪽 경계선 보다 작으면(위쪽이면) 아래쪽으로 이동이 가능
			if (m_Y < maxY)
			{
				m_Y = std::min<float>(m_Y + _distance, maxY);
				return true;
			}
		}
		break;

	case Direction::LEFT:
		{
			// 현재 x좌표가 왼쪽 경계선 보다 크면(오른쪽이면) 왼쪽으로 이동이 가능
			if (m_X > minX)
			{
				// 거리 2배를 곱하는 이유는 x좌표가 y좌표의 절반이기 때문
				m_X = std::max<float>(m_X - _distance, minX);
				return true;
			}
		}
		break;

	case Direction::RIGHT:
		{
			// 현재 x좌표가 왼쪽 경계선 보다 작으면(왼쪽이면) 오른쪽으로 이동이 가능
			if (m_X < maxX)
			{
				m_X = std::min<float>(m_X + _distance, maxX);
				return true;
			}
		}
		break;
	}
	return false;
    /// > 여기 마지막에 return false; 가 누락되어 있어서, 바운더리 도착시 방향전환이 안되고 있습니다.
    /// > 그래서 실행하면 다 한쪽으로 뭉치는 현상이 발생..;ㅁ;
	// 아하......! 그래서 그런 거였군여!! @_@! 따흐흑 감사합니다...! 이제 잘 되네여!!! ㅎㅎㅎ
}
