#include "pch.h"
#include "SnakeHead.h"
#include "Console.h"
#include "GameManager.h"

SnakeHead::SnakeHead()
	: m_Speed(1.f)
	, m_CurDir(Direction::UP)
    /// > �ʱⰪ�� 0�̾ ó���� ����Ű�� ������ �̵��� �ȵǳ׿�;��;
    /// > XŰ�� ������ �̼��� ���������ָ� �����̰� �Ǳ� ������,
    /// > �ʱ� �̼��� ��������� �־���� ���� �� �մϴ�..!
	// �ܳ�! �ʱ� �̼� �־����ϴ�!! �����մϴ�!! ��������
{
}

SnakeHead::~SnakeHead()
{
	//  ���࿡ ������ ������ �Բ� �Ҵ����� ���ش�.
	for (auto& pTail : m_TailList)
	{
		delete pTail;
	}
}

void SnakeHead::Update()
{
	// �ӽ÷� 10% Ȯ���� ���� �߰�
	if (rand() % 100 < 10)
	{
		AddTail();
	}

	// �����̱� ���� ���� ��ġ ����
	// ���� ������ �� ������ ��ġ�� �̵�
	float prevX = m_X;
	float prevY = m_Y;

	Move(m_CurDir, m_Speed);

	// �� ������ ���� ������ ��ġ�� ���� >> ��, ���󰡴� ���°� �ȴ�.
	for (auto& pTail : m_TailList)
	{
		float tempX = pTail->GetX();
		float tempY = pTail->GetY();
		pTail->SetX(prevX);
		pTail->SetY(prevY);
		prevX = tempX;
		prevY = tempY;
	}

	// ������ �ڿ� �Ӹ��� ������ ��Ҵ��� üũ�Ͽ� ���� ���� ó��
	for (auto& pTail : m_TailList)
	{
		// �� ������Ʈ�� ũ��� 1�� �����̹Ƿ�
		// �� ������Ʈ�� X, Y �Ÿ��� ��� 1 �̳��̸� ���� �ִ� ���̴�.
		if (m_X > pTail->GetX() - 0.5f &&
			m_X < pTail->GetX() + 0.5f &&
			m_Y < pTail->GetY() - 0.5f &&
			m_Y > pTail->GetY() + 0.5f)
		{
			// �ϴ� �浹 �� �ٷ� ���� ���� �ǵ��� ����
			GameManager::GetInstance().Shutdown();
			return;
			
			// Q. �� ���ᰡ �� �� ���...? �׳� �� �� ���µ�.....
		}
	}
}

void SnakeHead::Render()
{
	Object::Render();

	// ������ ���� �����鵵 ������
	for (auto& pTail : m_TailList)
	{
		pTail->Render();
	}
}

void SnakeHead::OnKeyPress(BYTE _key)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	// Move() �Լ��� �̵� ������ ����!
	// ���� ���� �ۼ����� �ʰ� �����ϰ� © �� �ְ� �Ǿ���!

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
	// ������ ���⸸ �ٲ��� �� �ִ�.
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
            /// > max �Լ��� ���ڷ� �Ѿ�� �� �μ� �߿� �� ū ���� �����ϴ� �Լ��Դϴ�.
            /// > ���� ���� ����� ��(m_Speed - 0.1f)�� �ּ��� ������ ��(0.1f)�� �Ѱܼ� max�Լ��� ȣ���� ���̰�
            /// > ��, ���� ����� ���� 0.1f���� ũ�� �� ���� ä�õǰ�
            /// > ���� 0.1f���� ���� ���̶�� �� ���� ������ 0.1f�� ��ȯ�Ѵٴ� �ǹ��Դϴ�.
            /// > ��, '�ִ� 0.1������ �ȴ�'�� �ƴ϶� '�ּ� 0.1������ �ȴ�'�� �½��ϴ�.
            /// > min �Լ��� ��쵵 ���Ͱ��� ������ �����ϸ� �˴ϴ�.
            /// > ��, m_Speed + 0.1f �� ���� ���� 3.0f ���Ͽ��� �� ���� ���̴� ���Դϴ�.
			// ������ �׷�����!! ���� ���ذ� �Ǿ����!! �����մϴ�!!!!
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

void SnakeHead::AddTail()
{
	Object* pTail = new Object();
	pTail->SetShape(L'��');
	m_TailList.push_back(pTail);
}
