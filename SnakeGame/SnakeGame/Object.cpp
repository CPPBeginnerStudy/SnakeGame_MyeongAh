#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
	: m_Shape(L' ') // wchar_t�� �ٲ�����Ƿ�, L' '�� ����� �Ѵ�.
	, m_X(0.f)
	, m_Y(0.f)
{
}

Object::~Object()
{
}

void Object::Update()
{
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
	// m_X�� 2�� �ϴ� ������ cmd���� X��ǥ ���̰� Y��ǥ ������ �����̱� ����! 
	Console::GetInstance().Print(m_Shape, (short)(m_X * 2), (short)m_Y);
}

bool Object::Move(Direction _dir, float _distance)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	// cmd ��ǥ���� boundaryBox�� �ΰ��� ��ǥ��� ��ȯ�Ͽ� ����ϵ��� �Ѵ�.
	// cmd ��ǥ�迡���� X ���̰� Y ������ �����̱� ������ �ΰ��� ��ǥ��� ������ �ٷ� ���⿡ �������ϴ�.
	float minX = (float) boundaryBox.left / 2;
	float maxX = (float) boundaryBox.right / 2;
	float minY = (float) boundaryBox.top;
	float maxY = (float) boundaryBox.bottom;

	switch (_dir)
	{
	case Direction::UP:
		{
			// ���� y��ǥ�� ���� ��輱 ���� ũ��(�Ʒ����̸�) ���� �̵��� ����
			if (m_Y > minY)
			{
				// ��û�� �Ÿ���ŭ �̵��� �õ��ϸ�, �ٿ������ �Ѿ�� �ʵ��� ó���Ѵ�.
				// std::max�� �� ���� ���� �� �� ū ���� ��ȯ�ϴ� �Լ��̴�.
				// m_Y - _distance�� �ٿ�������� ������ �ٿ���� ���� ��ȯ�Ͽ�, �� ���� ���� ������ �ʵ��� �Ѵ�.
				m_Y = std::max<float>(m_Y - _distance, minY);

				//���⿡ �Դٴ� ���� �̵��� �ϰ� �ִٴ� ���̴�.
				return true;
			}
		}
		break;

	case Direction::DOWN:
		{
			// ���� y��ǥ�� �Ʒ��� ��輱 ���� ������(�����̸�) �Ʒ������� �̵��� ����
			if (m_Y < maxY)
			{
				m_Y = std::min<float>(m_Y + _distance, maxY);
				return true;
			}
		}
		break;

	case Direction::LEFT:
		{
			// ���� x��ǥ�� ���� ��輱 ���� ũ��(�������̸�) �������� �̵��� ����
			if (m_X > minX)
			{
				// �Ÿ� 2�踦 ���ϴ� ������ x��ǥ�� y��ǥ�� �����̱� ����
				m_X = std::max<float>(m_X - _distance, minX);
				return true;
			}
		}
		break;

	case Direction::RIGHT:
		{
			// ���� x��ǥ�� ���� ��輱 ���� ������(�����̸�) ���������� �̵��� ����
			if (m_X < maxX)
			{
				m_X = std::min<float>(m_X + _distance, maxX);
				return true;
			}
		}
		break;
	}
	return false;
    /// > ���� �������� return false; �� �����Ǿ� �־, �ٿ���� ������ ������ȯ�� �ȵǰ� �ֽ��ϴ�.
    /// > �׷��� �����ϸ� �� �������� ��ġ�� ������ �߻�..;��;
	// ����......! �׷��� �׷� �ſ�����!! @_@! ������ �����մϴ�...! ���� �� �ǳ׿�!!! ������
}
