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

	// Move() �Լ��� �̵� ������ ����!
	// ���� ���� �ۼ����� �ʰ� �����ϰ� © �� �ְ� �Ǿ���!

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
			// �̵� �ӵ� ���̱� (�ּ� 0.1��)
			m_Speed = std::max<float>(m_Speed - 0.1f, 0.1f);
			// Q. ���̱� ���̱� min, max ��Ŵ�
			//    max�� ��, �پ��� �� �ִ� 0.1������ �پ��� �� �ǰ���??
			//	                        �ּ� 0.1���� �پ��ٰ� �ƴϱ���...
			//    min�� ��, �þ�� �� �ִ� 3.0���� �þ�� �� �ƴ϶�
			//                          �ּ� 3.0���� �þ�ٴ�??? @_@??
			// �׷���.. ���� �����ϴ� �� �������?
			// A < X < B �� ��, X�� �ּ� A���� �ִ� B���������� �����Ѵٰ� �ϸ�
			// �ּҰ� A�� �ִ� 0.1������ �ȴ� �̹Ƿ� max�� ���� ���̰�
			// �ִ밪 B�� �ּ� 3.0������ �ȴ� �̹Ƿ� min�� ���� ���̶�� ���ϱ��...?
			// �򰥸��׿�...@_@
		}
		break;

	case 'X':
		{
			// �̵� �ӵ� �ø��� (�ִ� 3��)
			m_Speed = std::min<float>(m_Speed + 0.1f, 3.0f);
		}
		break;
	}

}
