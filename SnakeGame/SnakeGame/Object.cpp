#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
	: m_Shape(L' ') // wchar_t�� �ٲ�����Ƿ�, L' '�� ����� �Ѵ�.
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
	// ȭ���� �ٿ������ ����� �ϸ�, �ݴ� �������� ��ȯ�Ͽ� ��� �����̵��� �Ѵ�.
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
	/// > ���� srand()�� ���� ������ �����߾��׿�.
	/// > srand()�� rand()����� ������ ȣ���ϴ� ���� �ƴ϶�
	/// > ���� ���۽� �� �ѹ��� ȣ��Ǿ�� �մϴ�. (GameManager::Init()����)
	/// > srand()�� �Ź� ȣ��Ǹ� �� ������ �����õ�(�������� ���)�� ���ŵǾ
	/// > ��� rand()�� ������ �������� ��ȯ�ϰ� �Ǿ�����ϴ�.
	/// > srand()�� rand()�Լ��� ���� ������ �� �����ϴ� � ��ݰ��� �����ϴ� �Լ��Դϴ�.
	//srand((unsigned int)time(nullptr));

	// ���׿�����
	// �����ϰ� if���� ���� �б� ó���� �ϰ� ���� �� ���
	// 3���� ������ �̷���� �־�, ���׿����ڶ�� �θ���,
	// ù �׿����� true/false ���ο� ���� true�̸� ��°��, false�̸� ��°���� ����
	// (�򰡽�) ? (true�� ���) : (false�� ���)
	if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, 1.f))
	{
		// m_IsRight�� ���� true�� ��� Move()�Լ��� ���ڷ� RIGHT�� �ѱ�� �ǰ�,
		//					false�� ��� LEFT�� �ѱ�� �ϴ� �ڵ�
		// �̵��� �����ϸ�(�ٿ������ �ɸ���) �ݴ� �������� ��ȯ
		// bool�� ������ �ڽ��� ���� ������Ű�� �ڵ� (true->false, false->true)
		m_IsRight = !m_IsRight;
	}
	if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, 1.f))
	{
		m_IsBottom = !m_IsBottom;
	}

	// �ߺ� �ڵ�� �̰� �Լ��� ������!
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
	// ���� �� ��ġ(m_X, m_Y)�� �� ���(m_Shape)�� �׸����� �Ѵ�.
	// �Ǽ��� ������ �ٲپ� �־�����, ������ ��Ʈ ���̶� ��ǥ�� �Ǽ��� ���� �� ���
	// ������ short�� ����ȯ �ؼ� Print�� �־��ش�. (print�� �޴� ���ڵ� �Ǽ����� �ƴ�)
	Console::GetInstance().Print(m_Shape, (short)m_X, (short)m_Y);
}

bool Object::Move(Direction _dir, float _distance)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
	switch (_dir)
	{
	case Direction::UP:
		{
			// ���� y��ǥ�� ���� ��輱 ���� ũ��(�Ʒ����̸�) ���� �̵��� ����
			if (m_Y > boundaryBox.top)
			{
				// ��û�� �Ÿ���ŭ �̵��� �õ��ϸ�, �ٿ������ �Ѿ�� �ʵ��� ó���Ѵ�.
				// std::max�� �� ���� ���� �� �� ū ���� ��ȯ�ϴ� �Լ��̴�.
				// m_Y - _distance�� �ٿ�������� ������ �ٿ���� ���� ��ȯ�Ͽ�, �� ���� ���� ������ �ʵ��� �Ѵ�.
				m_Y = std::max<float>(m_Y - _distance, boundaryBox.top);

				//���⿡ �Դٴ� ���� �̵��� �ϰ� �ִٴ� ���̴�.
				return true;
			}
		}
		break;

	case Direction::DOWN:
		{
			// ���� y��ǥ�� �Ʒ��� ��輱 ���� ������(�����̸�) �Ʒ������� �̵��� ����
			if (m_Y < boundaryBox.bottom)
			{
				m_Y = std::min<float>(m_Y + _distance, boundaryBox.bottom);
				return true;
			}
		}
		break;

	case Direction::LEFT:
		{
			// ���� x��ǥ�� ���� ��輱 ���� ũ��(�������̸�) �������� �̵��� ����
			if (m_X > boundaryBox.left)
			{
				// �Ÿ� 2�踦 ���ϴ� ������ x��ǥ�� y��ǥ�� �����̱� ����
				m_X = std::max<float>(m_X - _distance * 2, boundaryBox.left);
				return true;
			}
		}
		break;

	case Direction::RIGHT:
		{
			// ���� x��ǥ�� ���� ��輱 ���� ������(�����̸�) ���������� �̵��� ����
			if (m_X < boundaryBox.right)
			{
				m_X = std::min<float>(m_X + _distance * 2, boundaryBox.right);
				return true;
			}
		}
		break;
	}

}
