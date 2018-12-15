#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
	: m_Shape(L' ') // wchar_t�� �ٲ�����Ƿ�, L' '�� ����� �Ѵ�.
	, m_X(0)
	, m_Y(0)
	, m_IsRight(true)
	, m_IsBottom(false)
	, m_VelocityX(1)
	, m_VelocityY(1)
	, m_VelFlagX(false)
	, m_VelFlagY(false)
{
}

Object::~Object()
{
}

void Object::Init()
{
}

void Object::Release()
{
}

void Object::Update()
{
	// ȭ���� �ٿ������ ����� �ϸ�, �ݴ� �������� ��ȯ�Ͽ� ��� �����̵��� �Ѵ�.
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	if (m_IsRight)
	{
		m_X += m_VelocityX;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
			m_VelFlagX = true;
		}
	}
	else
	{
		m_X -= m_VelocityX;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;
			m_VelFlagX = true;
		}
	}
	if (m_VelFlagX)
	{
        /// > ���� srand()�� ���� ������ �����߾��׿�.
        /// > srand()�� rand()����� ������ ȣ���ϴ� ���� �ƴ϶�
        /// > ���� ���۽� �� �ѹ��� ȣ��Ǿ�� �մϴ�. (GameManager::Init()����)
        /// > srand()�� �Ź� ȣ��Ǹ� �� ������ �����õ�(�������� ���)�� ���ŵǾ
        /// > ��� rand()�� ������ �������� ��ȯ�ϰ� �Ǿ�����ϴ�.
        /// > srand()�� rand()�Լ��� ���� ������ �� �����ϴ� � ��ݰ��� �����ϴ� �Լ��Դϴ�.
		//srand((unsigned int)time(nullptr));

		m_VelocityX = (rand() % 3) + 1;
		m_VelFlagX = false;
	}

	if (m_IsBottom)
	{
		m_Y += m_VelocityY;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
			m_VelFlagY = true;
		}
	}
	else
	{
		m_Y -= m_VelocityY;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
			m_VelFlagY = true;
		}
	}
	if (m_VelFlagY)
	{
		//srand((unsigned int)time(nullptr));

		m_VelocityY = (rand() % 3) + 1;
		m_VelFlagY = false;
	}
}

void Object::Render()
{
	// ���� �� ��ġ(m_X, m_Y)�� �� ���(m_Shape)�� �׸����� �Ѵ�.
	Console::GetInstance().Print(m_Shape, m_X, m_Y);
}
