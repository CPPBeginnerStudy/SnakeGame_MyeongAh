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
	: m_XSpeed(0.f)
	, m_YSpeed(0.f)
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

void RandomSpeedObj::Update()
{
	// Update()�� ���� ���Ӱ� ������ �������ϱ� ����
	// �θ��� Update()�� ȣ������ ���� �� ����.
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
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
}

void RandomSpeedObj::Render()
{
	Object::Render();
}