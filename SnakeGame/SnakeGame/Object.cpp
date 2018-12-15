#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
	: m_Shape(L' ') // wchar_t로 바뀌었으므로, L' '로 해줘야 한다.
	, m_X(0.f)
	, m_Y(0.f)
	, m_IsRight(false)
	, m_IsBottom(false)
{
}

Object::~Object()
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

	// 삼항연산자
	// 간단하게 if문과 같은 분기 처리를 하고 싶을 때 사용
	// 3개의 항으로 이루어져 있어, 삼항연산자라고 부르며,
	// 첫 항에서의 true/false 여부에 따라 true이면 둘째항, false이면 셋째항을 수행
	// (평가식) ? (true인 경우) : (false인 경우)
	if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, 1.f))
	{
		// m_IsRight의 값이 true인 경우 Move()함수의 인자로 RIGHT를 넘기게 되고,
		//					false인 경우 LEFT를 넘기게 하는 코드
		// 이동이 실패하면(바운더리에 걸리면) 반대 방향으로 전환
		// bool값 변수가 자신의 값을 반전시키는 코드 (true->false, false->true)
		m_IsRight = !m_IsRight;
	}
	if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, 1.f))
	{
		m_IsBottom = !m_IsBottom;
	}

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
	Console::GetInstance().Print(m_Shape, (short)m_X, (short)m_Y);
}

bool Object::Move(Direction _dir, float _distance)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
	switch (_dir)
	{
	case Direction::UP:
		{
			// 현재 y좌표가 위쪽 경계선 보다 크면(아래쪽이면) 위로 이동이 가능
			if (m_Y > boundaryBox.top)
			{
				// 요청한 거리만큼 이동을 시도하며, 바운더리를 넘어서지 않도록 처리한다.
				// std::max는 두 개의 인자 중 더 큰 것을 반환하는 함수이다.
				// m_Y - _distance가 바운더리보다 작으면 바운더리 값을 반환하여, 그 이하 값이 나오지 않도록 한다.
				m_Y = std::max<float>(m_Y - _distance, boundaryBox.top);

				//여기에 왔다는 것은 이동은 하고 있다는 뜻이다.
				return true;
			}
		}
		break;

	case Direction::DOWN:
		{
			// 현재 y좌표가 아래쪽 경계선 보다 작으면(위쪽이면) 아래쪽으로 이동이 가능
			if (m_Y < boundaryBox.bottom)
			{
				m_Y = std::min<float>(m_Y + _distance, boundaryBox.bottom);
				return true;
			}
		}
		break;

	case Direction::LEFT:
		{
			// 현재 x좌표가 왼쪽 경계선 보다 크면(오른쪽이면) 왼쪽으로 이동이 가능
			if (m_X > boundaryBox.left)
			{
				// 거리 2배를 곱하는 이유는 x좌표가 y좌표의 절반이기 때문
				m_X = std::max<float>(m_X - _distance * 2, boundaryBox.left);
				return true;
			}
		}
		break;

	case Direction::RIGHT:
		{
			// 현재 x좌표가 왼쪽 경계선 보다 작으면(왼쪽이면) 오른쪽으로 이동이 가능
			if (m_X < boundaryBox.right)
			{
				m_X = std::min<float>(m_X + _distance * 2, boundaryBox.right);
				return true;
			}
		}
		break;
	}

}
