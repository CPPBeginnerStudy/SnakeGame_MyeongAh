#include "pch.h"
#include "RandomSpeedObj.h"
#include "Console.h""


// 상속받은 클래스의 생성자는 부모 클래스의 생성자가 먼저 호출된 이후에 호출된다.
// 따로 코드를 추가하지 않아도 위의 순서로 자동으로 수행된다.
// 따라서, 자식 클래스들은 부모 클래스의 멤버 변수 초기화를 신경쓰지 않아도 된다.
// 부모 클래스에 있는 생성자가 알아서 하기 때문
// 예제 코드)
// class A { virtual ~A(){} }
// class B : public A { virtual ~B(){} }
// class C : public B { virtual ~C(){} }
// int main()
// {
//		C* pC = new C(); // A생성자 -> B생성자 -> C생성자 순으로 호출됨
// }
RandomSpeedObj::RandomSpeedObj()
	: m_XSpeed(1)
	, m_YSpeed(1)
	, m_IsRight(false)
	, m_IsBottom(false)
{
	m_Shape = L'★';
	m_Color = Color::YELLOW;
}

// 상속받은 클래스의 소멸자는 자신이 먼저 호출된 후, 부모 클래스의 소멸자를 호출한다.
// 따로 코드를 추가하지 않아도 위의 순서로 자동으로 수행된다.
// 생성자와 호출 순서가 반대인 이유는
// 할당 해제가 할당된 순서의 반대로 진행되어야 안전하고 효율적이기 때문이다.
// 예제 코드)
// class A { virtual ~A(){} }
// class B : public A { virtual ~B(){} }
// class C : public B { virtual ~C(){} }
// int main()
// {
//		C* pC = new C(); // A생성자 -> B생성자 -> C생성자 순으로 호출됨
//		delete pC;		 // C소멸자 -> B소멸자 -> A소멸자 순으로 호출됨
//		// 생성자는 항상 실제 자신을 아는 상태이기 때문에 virtual 키워드가 필요 없지만
//		// 소멸자는 소멸 시점에 부모 클래스 포인터 타입에 저장된 변수를 통해 delete할 가능성이 있기 때문에
//		// virtual 키워드가 없다면 실제 자신의 소멸자를 찾을 수가 없으므로, 반드시 키워드를 추가해야 한다.
//		// 위 코드에서 만약 virtual 키워드가 없었다면, A소멸자만 호출되어 메모리 릭이 발생하게 된다.
// } 
RandomSpeedObj::~RandomSpeedObj()
{
}

// 앞으로 필요 없을 것 같아 지운다.
/*
void RandomSpeedObj::Init()
{
	// 오버라이딩 한 함수는 기본적으로 부모 함수를 호출하지 않는다.
	// 부모함수도 호출할 필요가 있을 경우 아래와 같이 부모 클래스::함수명 으로 호출해준다.
	// Init()의 경우는 부모의 Init()을 먼저 호출하고, 추가로 나(자식)가 초기화할 것을 해준다.
	Object::Init();
	m_XSpeed = 1.f;
	m_YSpeed = 1.f;
}

void RandomSpeedObj::Release()
{
	// 부모 클래스와 다르게 구현할 게 없다면, 그냥 부모꺼를 여기서 다시 호출해주면 된다.
	Object::Release();
}
*/

void RandomSpeedObj::Update(float _dt)
{
	/*
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
	// Move()의 리턴 값이 false일 때 (즉, 바운더리에 닿았을 때)
	// 방향을 반전시키고 속도를 랜덤으로 변경하는 코드
	// 기존의 공통된 로직(이동 로직)을 Move()라는 함수로 추출하여
	// 중복 코드를 줄이고 차이점을 파악하기 더 쉬워졌다.
	*/

	// 화면의 바운더리를 벗어나려 하면, 반대 방향으로 전환하여 계속 움직이도록 한다.
	//RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
	/// > 제가 srand()에 대한 설명이 부족했었네요.
	/// > srand()는 rand()사용할 때마다 호출하는 것이 아니라
	/// > 게임 시작시 딱 한번만 호출되어야 합니다. (GameManager::Init()에서)
	/// > srand()가 매번 호출되면 그 때마다 랜덤시드(랜덤값의 기반)이 갱신되어서
	/// > 모든 rand()가 동일한 랜덤값을 반환하게 되어버립니다.
	/// > srand()는 rand()함수가 값을 산출할 때 참고하는 어떤 기반값을 설정하는 함수입니다.
	//srand((unsigned int)time(nullptr));

	// 삼항연산자
	// 간단하게 if문과 같은 분기 처리를 하고 싶을 때 사용
	// 3개의 항으로 이루어져 있어, 삼항연산자라고 부르며,
	// 첫 항에서의 true/false 여부에 따라 true이면 둘째항, false이면 셋째항을 수행
	// (평가식) ? (true인 경우) : (false인 경우)
	if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, m_XSpeed))
	{
		// m_IsRight의 값이 true인 경우 Move()함수의 인자로 RIGHT를 넘기게 되고,
		//					false인 경우 LEFT를 넘기게 하는 코드
		// 이동이 실패하면(바운더리에 걸리면) 반대 방향으로 전환
		// bool값 변수가 자신의 값을 반전시키는 코드 (true->false, false->true)
		m_IsRight = !m_IsRight;

		// 1~3으로 이동속도 랜덤 조정
		m_XSpeed = rand() % 3 + 1;
	}
	if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, m_YSpeed))
	{
		m_IsBottom = !m_IsBottom;
		m_YSpeed = rand() % 3 + 1;
	}

	/*
	if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, m_XSpeed))
	{
		m_IsRight = !m_IsRight;
		m_XSpeed = (rand() % 6 + 1) * 0.5f; // 0.5배 ~ 3배
	}
	if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, m_YSpeed))
	{
		m_IsBottom = !m_IsBottom;
		m_YSpeed = (rand() % 6 + 1) * 0.5f;
	}
	*/

	/*
	// Update()의 경우는 새롭게 구현을 재정의하기 위해
	// 부모의 Update()를 호출하지 않은 점 참고.
	if (m_IsRight)
	{
		m_X += 2 * m_XSpeed;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
			m_XSpeed = (rand() % 6 + 1) * 0.5f; // 0.5배 ~ 3배
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
	// 오버라이딩한 함수는 기본적으로 부모함수를 호출하지 않는다.
	// 따라서 부모함수도 호출할 필요가 있을 경우 아래와같이 부모클래스::함수명 으로 호출해준다.
	// 부모클래스의 구현과 다르게 처리할 게 없다면, 그냥 부모꺼를 여기다 다시 호출해주면 된다.
	Object::Render();
}

bool RandomSpeedObj::HitCheck(Object * _pOther)
{
	return Object::HitCheck(_pOther);
}

void RandomSpeedObj::OnHit(Object * _pHitter)
{
	Object::OnHit(_pHitter);
}
