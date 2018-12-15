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
			// x 좌표는 y 좌표의 절반이므로 동일한 비율로 움직이려면 2배 해줘야 함
			m_X -= 2 * m_Speed;
			if (m_X < boundaryBox.left)
			{
				m_X = boundaryBox.left;
			}
		}
		break;

	case VK_RIGHT:
		{
			// x 좌표는 y 좌표의 절반이므로 동일한 비율로 움직이려면 2배 해줘야 함
			m_X += 2 * m_Speed;
			if (m_X < boundaryBox.right)
			{
				m_X = boundaryBox.right;
			}
		}
		break;

	case 'Z':
		{
			// 이동 속도 줄이기
			m_Speed -= 0.1f;
			if (m_Speed < 0.1f)
			{
				m_Speed = 0.1f;
			}
		}
		break;

	case 'X':
		{
			// 이동 속도 늘리기
			m_Speed += 0.1f;
			if (m_Speed > 3.f)
			{
				m_Speed = 3.f;
			}
		}
		break;
	}

}
