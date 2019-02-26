#include "pch.h"
#include "RandomSpeedObj.h"
#include "Console.h"


// ��ӹ��� Ŭ������ �����ڴ� �θ� Ŭ������ �����ڰ� ���� ȣ��� ���Ŀ� ȣ��ȴ�.
// ���� �ڵ带 �߰����� �ʾƵ� ���� ������ �ڵ����� ����ȴ�.
// ����, �ڽ� Ŭ�������� �θ� Ŭ������ ��� ���� �ʱ�ȭ�� �Ű澲�� �ʾƵ� �ȴ�.
// �θ� Ŭ������ �ִ� �����ڰ� �˾Ƽ� �ϱ� ����
// ���� �ڵ�)
// class A { virtual ~A(){} }
// class B : public A { virtual ~B(){} }
// class C : public B { virtual ~C(){} }
// int main()
// {
//		C* pC = new C(); // A������ -> B������ -> C������ ������ ȣ���
// }
RandomSpeedObj::RandomSpeedObj()
	: m_XSpeed(1.f)
	, m_YSpeed(1.f)
	, m_IsRight(false)
	, m_IsBottom(false)
{
}

// ��ӹ��� Ŭ������ �Ҹ��ڴ� �ڽ��� ���� ȣ��� ��, �θ� Ŭ������ �Ҹ��ڸ� ȣ���Ѵ�.
// ���� �ڵ带 �߰����� �ʾƵ� ���� ������ �ڵ����� ����ȴ�.
// �����ڿ� ȣ�� ������ �ݴ��� ������
// �Ҵ� ������ �Ҵ�� ������ �ݴ�� ����Ǿ�� �����ϰ� ȿ�����̱� �����̴�.
// ���� �ڵ�)
// class A { virtual ~A(){} }
// class B : public A { virtual ~B(){} }
// class C : public B { virtual ~C(){} }
// int main()
// {
//		C* pC = new C(); // A������ -> B������ -> C������ ������ ȣ���
//		delete pC;		 // C�Ҹ��� -> B�Ҹ��� -> A�Ҹ��� ������ ȣ���
//		// �����ڴ� �׻� ���� �ڽ��� �ƴ� �����̱� ������ virtual Ű���尡 �ʿ� ������
//		// �Ҹ��ڴ� �Ҹ� ������ �θ� Ŭ���� ������ Ÿ�Կ� ����� ������ ���� delete�� ���ɼ��� �ֱ� ������
//		// virtual Ű���尡 ���ٸ� ���� �ڽ��� �Ҹ��ڸ� ã�� ���� �����Ƿ�, �ݵ�� Ű���带 �߰��ؾ� �Ѵ�.
//		// �� �ڵ忡�� ���� virtual Ű���尡 �����ٸ�, A�Ҹ��ڸ� ȣ��Ǿ� �޸� ���� �߻��ϰ� �ȴ�.
// } 
RandomSpeedObj::~RandomSpeedObj()
{
}

// ������ �ʿ� ���� �� ���� �����.
/*
void RandomSpeedObj::Init()
{
	// �������̵� �� �Լ��� �⺻������ �θ� �Լ��� ȣ������ �ʴ´�.
	// �θ��Լ��� ȣ���� �ʿ䰡 ���� ��� �Ʒ��� ���� �θ� Ŭ����::�Լ��� ���� ȣ�����ش�.
	// Init()�� ���� �θ��� Init()�� ���� ȣ���ϰ�, �߰��� ��(�ڽ�)�� �ʱ�ȭ�� ���� ���ش�.
	Object::Init();
	m_XSpeed = 1.f;
	m_YSpeed = 1.f;
}

void RandomSpeedObj::Release()
{
	// �θ� Ŭ������ �ٸ��� ������ �� ���ٸ�, �׳� �θ𲨸� ���⼭ �ٽ� ȣ�����ָ� �ȴ�.
	Object::Release();
}
*/

void RandomSpeedObj::Update()
{
	/*
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
	// Move()�� ���� ���� false�� �� (��, �ٿ������ ����� ��)
	// ������ ������Ű�� �ӵ��� �������� �����ϴ� �ڵ�
	// ������ ����� ����(�̵� ����)�� Move()��� �Լ��� �����Ͽ�
	// �ߺ� �ڵ带 ���̰� �������� �ľ��ϱ� �� ��������.
	*/

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

	/*
	if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, m_XSpeed))
	{
		m_IsRight = !m_IsRight;
		m_XSpeed = (rand() % 6 + 1) * 0.5f; // 0.5�� ~ 3��
	}
	if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, m_YSpeed))
	{
		m_IsBottom = !m_IsBottom;
		m_YSpeed = (rand() % 6 + 1) * 0.5f;
	}
	*/

	/*
	// Update()�� ���� ���Ӱ� ������ �������ϱ� ����
	// �θ��� Update()�� ȣ������ ���� �� ����.
	if (m_IsRight)
	{
		m_X += 2 * m_XSpeed;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
			m_XSpeed = (rand() % 6 + 1) * 0.5f; // 0.5�� ~ 3��
		}
	}
	else
	{
		m_X -= 2 * m_XSpeed;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;
			m_XSpeed = (rand() % 6 + 1) * 0.5f;
		}
	}
	if (m_IsBottom)
	{
		m_Y += 1 * m_YSpeed;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
			m_YSpeed = (rand() % 6 + 1) * 0.5f;
		}
	}
	else
	{
		m_Y -= 1 * m_YSpeed;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
			m_YSpeed = (rand() % 6 + 1) * 0.5f;
		}
	}
	*/
}

void RandomSpeedObj::Render()
{
	// �������̵��� �Լ��� �⺻������ �θ��Լ��� ȣ������ �ʴ´�.
	// ���� �θ��Լ��� ȣ���� �ʿ䰡 ���� ��� �Ʒ��Ͱ��� �θ�Ŭ����::�Լ��� ���� ȣ�����ش�.
	// �θ�Ŭ������ ������ �ٸ��� ó���� �� ���ٸ�, �׳� �θ𲨸� ����� �ٽ� ȣ�����ָ� �ȴ�.
	Object::Render();
}