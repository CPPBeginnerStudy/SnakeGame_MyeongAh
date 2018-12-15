#include "pch.h"
#include "SnakeHead.h"
#include "Console.h"

SnakeHead::SnakeHead()
	: m_Speed(0.f)
    /// > 초기값이 0이어서 처음에 방향키를 눌러도 이동이 안되네요;ㅁ;
    /// > X키를 눌러서 이속을 증가시켜주면 움직이게 되긴 하지만,
    /// > 초기 이속이 어느정도는 있어줘야 좋을 듯 합니다..!
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
            /// > max 함수는 인자로 넘어온 두 인수 중에 더 큰 값을 선택하는 함수입니다.
            /// > 따라서 새로 계산한 값(m_Speed - 0.1f)과 최소한 유지할 값(0.1f)을 넘겨서 max함수를 호출한 것이고
            /// > 즉, 새로 계산한 값이 0.1f보다 크면 그 값이 채택되고
            /// > 만약 0.1f보다 낮은 값이라면 그 값은 버리고 0.1f를 반환한다는 의미입니다.
            /// > 즉, '최대 0.1까지만 된다'가 아니라 '최소 0.1까지만 된다'가 맞습니다.
            /// > min 함수의 경우도 위와같은 원리로 생각하면 됩니다.
            /// > 즉, m_Speed + 0.1f 로 계산된 값이 3.0f 이하여야 그 값이 쓰이는 것입니다.
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
