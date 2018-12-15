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

	switch (_key)
	{
	case VK_UP:
		{
			m_Y -= 1 * m_Speed;
			if (m_Y < boundaryBox.top)
			{
				m_Y = boundaryBox.top;
			}
		}
		break;

	case VK_DOWN:
		{
			m_Y += 1 * m_Speed;
			if (m_Y < boundaryBox.bottom)
			{
				m_Y = boundaryBox.bottom;
			}
		}
		break;

	case VK_LEFT:
		{
			// x ��ǥ�� y ��ǥ�� �����̹Ƿ� ������ ������ �����̷��� 2�� ����� ��
			m_X -= 2 * m_Speed;
			if (m_X < boundaryBox.left)
			{
				m_X = boundaryBox.left;
			}
		}
		break;

	case VK_RIGHT:
		{
			// x ��ǥ�� y ��ǥ�� �����̹Ƿ� ������ ������ �����̷��� 2�� ����� ��
			m_X += 2 * m_Speed;
			if (m_X < boundaryBox.right)
			{
				m_X = boundaryBox.right;
			}
		}
		break;

	case 'Z':
		{
			// �̵� �ӵ� ���̱�
			m_Speed -= 0.1f;
			if (m_Speed < 0.1f)
			{
				m_Speed = 0.1f;
			}
		}
		break;

	case 'X':
		{
			// �̵� �ӵ� �ø���
			m_Speed += 0.1f;
			if (m_Speed > 3.f)
			{
				m_Speed = 3.f;
			}
		}
		break;
	}

}
