#include "pch.h"
#include "SnakeHead.h"
#include "Console.h"

SnakeHead::SnakeHead()
	: m_Speed(0.f)
{
}

SnakeHead::~SnakeHead()
{
}

void SnakeHead::Update()
{
}

void SnakeHead::Render()
{
	Object::Render();
}

void SnakeHead::OnKeyPress(BYTE _key)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	// Move() 함수로 이동 로직을 통일!
	// 이제 각각 작성하지 않고 간결하게 짤 수 있게 되었다!

	switch (_key)
	{
	case VK_UP:
		{
			Move(Direction::UP, m_Speed);
		}
		break;

	case VK_DOWN:
		{
			Move(Direction::DOWN, m_Speed);
		}
		break;

	case VK_LEFT:
		{
			Move(Direction::LEFT, m_Speed);
		}
		break;

	case VK_RIGHT:
		{
			Move(Direction::RIGHT, m_Speed);
		}
		break;

	case 'Z':
		{
			// 이동 속도 줄이기 (최소 0.1배)
			m_Speed = std::max<float>(m_Speed - 0.1f, 0.1f);
			// Q. 늘이기 줄이기 min, max 요거는
			//    max일 때, 줄어드는 게 최대 0.1까지만 줄어든다 인 건가용??
			//	                        최소 0.1까지 줄어든다가 아니군요...
			//    min일 때, 늘어나는 게 최대 3.0까지 늘어나는 게 아니라
			//                          최소 3.0까지 늘어난다니??? @_@??
			// 그러믄.. 일케 이해하는 게 맞을까용?
			// A < X < B 일 때, X를 최소 A까지 최대 B까지만으로 한정한다고 하면
			// 최소값 A는 최대 0.1까지만 된다 이므로 max를 쓰는 것이고
			// 최대값 B는 최소 3.0까지만 된다 이므로 min을 쓰는 것이라는 뜻일까요...?
			// 헷갈리네여...@_@
		}
		break;

	case 'X':
		{
			// 이동 속도 늘리기 (최대 3배)
			m_Speed = std::min<float>(m_Speed + 0.1f, 3.0f);
		}
		break;
	}

}
