#include "pch.h"
#include "SnakeHead.h"
#include "Console.h"
#include "GameManager.h"

SnakeHead::SnakeHead()
	: m_Speed(1.f)
	, m_CurDir(Direction::UP)
    /// > 초기값이 0이어서 처음에 방향키를 눌러도 이동이 안되네요;ㅁ;
    /// > X키를 눌러서 이속을 증가시켜주면 움직이게 되긴 하지만,
    /// > 초기 이속이 어느정도는 있어줘야 좋을 듯 합니다..!
	// 넵넵! 초기 이속 넣었습니당!! 감사합니다!! ㅎㅎㅎㅎ
{
}

SnakeHead::~SnakeHead()
{
	//  만약에 꼬리가 있으면 함께 할당해제 해준다.
	for (auto& pTail : m_TailList)
	{
		delete pTail;
	}
}

void SnakeHead::Update()
{
	// 임시로 10% 확률로 꼬리 추가
	if (rand() % 100 < 10)
	{
		AddTail();
	}

	// 움직이기 전에 원래 위치 보관
	// 다음 꼬리가 이 보관된 위치로 이동
	float prevX = m_X;
	float prevY = m_Y;

	Move(m_CurDir, m_Speed);

	// 각 꼬리는 이전 꼬리의 위치로 세팅 >> 즉, 따라가는 형태가 된다.
	for (auto& pTail : m_TailList)
	{
		float tempX = pTail->GetX();
		float tempY = pTail->GetY();
		pTail->SetX(prevX);
		pTail->SetY(prevY);
		prevX = tempX;
		prevY = tempY;
	}

	// 움직인 뒤에 머리가 꼬리에 닿았는지 체크하여 게임 오버 처리
	for (auto& pTail : m_TailList)
	{
		// 각 오브젝트의 크기는 1로 고정이므로
		// 두 오브젝트의 X, Y 거리가 모두 1 이내이면 겹쳐 있는 것이다.
		if (m_X > pTail->GetX() - 0.5f &&
			m_X < pTail->GetX() + 0.5f &&
			m_Y < pTail->GetY() - 0.5f &&
			m_Y > pTail->GetY() + 0.5f)
		{
			// 일단 충돌 시 바로 게임 종료 되도록 구현
			GameManager::GetInstance().Shutdown();
			return;
			
			// Q. 왜 종료가 안 될 까요...? 그냥 막 잘 가는데.....
		}
	}
}

void SnakeHead::Render()
{
	Object::Render();

	// 나에게 붙은 꼬리들도 렌더링
	for (auto& pTail : m_TailList)
	{
		pTail->Render();
	}
}

void SnakeHead::OnKeyPress(BYTE _key)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	// Move() 함수로 이동 로직을 통일!
	// 이제 각각 작성하지 않고 간결하게 짤 수 있게 되었다!

	switch (_key)
	{
	/*
	case VK_UP:
		{
			Move(Direction::UP, m_Speed);
			m_CurDir = Direction::UP;
		}
		break;

	case VK_DOWN:
		{
			Move(Direction::DOWN, m_Speed);
			m_CurDir = Direction::DOWN;
		}
		break;

	case VK_LEFT:
		{
			Move(Direction::LEFT, m_Speed);
			m_CurDir = Direction::LEFT;
		}
		break;

	case VK_RIGHT:
		{
			Move(Direction::RIGHT, m_Speed);
			m_CurDir = Direction::RIGHT;
		}
		break;
	*/
	// 유저는 방향만 바꿔줄 수 있다.
	case VK_UP:
	{
		m_CurDir = Direction::UP;
	}
	break;

	case VK_DOWN:
	{
		m_CurDir = Direction::DOWN;
	}
	break;

	case VK_LEFT:
	{
		m_CurDir = Direction::LEFT;
	}
	break;

	case VK_RIGHT:
	{
		m_CurDir = Direction::RIGHT;
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
			// 오오오 그렇군요!! 이제 이해가 되었어요!! 감사합니당!!!!
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

void SnakeHead::AddTail()
{
	Object* pTail = new Object();
	pTail->SetShape(L'※');
	m_TailList.push_back(pTail);
}
