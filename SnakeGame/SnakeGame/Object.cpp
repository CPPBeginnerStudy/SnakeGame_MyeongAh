#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
	: m_Shape(L' ') // wchar_t�� �ٲ�����Ƿ�, L' '�� ����� �Ѵ�.
	, m_X(0)
	, m_Y(0)
	, m_IsRight(false)
	, m_IsBottom(false)
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
	/// > ���� srand()�� ���� ������ �����߾��׿�.
	/// > srand()�� rand()����� ������ ȣ���ϴ� ���� �ƴ϶�
	/// > ���� ���۽� �� �ѹ��� ȣ��Ǿ�� �մϴ�. (GameManager::Init()����)
	/// > srand()�� �Ź� ȣ��Ǹ� �� ������ �����õ�(�������� ���)�� ���ŵǾ
	/// > ��� rand()�� ������ �������� ��ȯ�ϰ� �Ǿ�����ϴ�.
	/// > srand()�� rand()�Լ��� ���� ������ �� �����ϴ� � ��ݰ��� �����ϴ� �Լ��Դϴ�.
	//srand((unsigned int)time(nullptr));

	if (m_IsRight)
	{
		++m_X;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
		}
	}
	else
	{
		--m_X;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;
		}
	}
	if (m_IsBottom)
	{
		++m_Y;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
		}
	}
	else
	{
		--m_Y;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
		}
	}
}

void Object::Render()
{
	// ���� �� ��ġ(m_X, m_Y)�� �� ���(m_Shape)�� �׸����� �Ѵ�.
	Console::GetInstance().Print(m_Shape, m_X, m_Y);
}
