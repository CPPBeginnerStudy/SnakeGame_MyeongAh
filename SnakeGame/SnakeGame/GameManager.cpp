#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"

// 생성자, 소멸자는 이미 역할이 정해져 있어서, 반환 타입이 필요 없다. (void 이런거)
GameManager::GameManager()
	: m_IsOn(false)
{
}

GameManager::~GameManager()
{
}

void GameManager::Run()
{
	Init();
	MainLoop();
	Release();
}

void GameManager::Shutdown()
{
	// 게임을 OFF로 만들어서, 다음 프레임에 메인 루프에서 빠져나오도록 한다.
	m_IsOn = false;
}

void GameManager::Init()
{
	Console::GetInstance().Init();
	// 랜덤값 사용을 위해 랜덤시드를 초기화
	srand((unsigned int)time(nullptr));

	// Console 객체의 인스턴스를 가져와서 console이라는 참조변수에 저장하여 사용
	// 매번 Console::GetInstance()를 써주기 보단 이렇게 참조변수를 쓰면
	// 가독성 등 여러 측면에서 Good
	// auto 키워드는 대입되는 타입과 동일한 타입으로 자동으로 받아주는 역할
	auto& console = Console::GetInstance();	//(동일) Console& console = Console::GetInstance();
	console.Init();

	// 5개의 object를 생성하면서 바운더리 내에서 x, y 좌표를 매번 랜덤하게 지정
	RECT boundaryBox = console.GetBoundaryBox();
	for (int i = 0; i < 5; ++i)
	{
		Object* pObject = new Object();
		pObject->Init();
		pObject->SetShape('O');
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		pObject->SetVelocityX((rand() % 3) + 1);
		pObject->SetVelocityY((rand() % 3) + 1);
		m_objectList.push_back(pObject);
	}
	/*
	for (int i = 0; i < 5; i++)
	{
		Object* pObject = new Object();
		pObject->Init();
		// [->] 그 주소에 있는 녀석의 멤버 함수를 불러온다 (포인터)
		// [.]은 주소를 알고 있어서 걍 가져오는 것
		m_objectList.push_back(pObject);
	}
	*/
	// 모든 초기화 완료 되었으므로 게임 ON
	m_IsOn = true;
}

void GameManager::Release()
{
	// 현재 게임과 관련된 모든 객체들을 Release
	// 보통은 Init()에서 초기화 해준 객체들을 여기서 Release 해주면 됨
	// Heap 메모리에 New 해준 애들을 Delete 해주는 역할을 하는 곳
	// EX. 게임을 끝내고 메인 화면으로 돌아갔을 때 사용했던 것들을 정리하는 역할
	Console::GetInstance().Release();

	// 메모리 릭을 줄이려면, 뭔가 오브젝트 만들어서 해놓고 바로 릴리즈로 와서 delete 해주는 것이 좋음. 안 까먹게
	// m_ObjectList라는 자료구조에서 그 저장된 데이터를 저장된만큼 하나씩 가져오는 반복문
	for (auto& pObject : m_objectList) // 현재는 5개 보관중이므로 5번 실행됨
	{
		pObject->Release(); // 가져온 데이터(pObject)에 대해 Release() 호출
		delete pObject;     // 해당 인스턴스를 delete하여 메모리 할당 해제
	}

	// 보관중이던 모든 포인터들이 그 가리키던 인스턴스들을 다 할당 해제했으므로
	// m_ObjectList를 비워준다. 안하면 주인없는 포인터들을 가지고 있게 된다. (메모리 릭)
	m_objectList.clear();
}

void GameManager::MainLoop()
{
	while (m_IsOn)
	{
		// 한 프레임마다 업데이트, 랜더링 진행
		Update();
		Render();

		// Sleep()함수는 인자로 받은 수치만큼(밀리세컨드 단위) 프로그램을 정지시킨다.
		// 메인 루프가 너무 빨리 돌면 화면을 알아보기 힘들기 때문에, 0.03초마다 한 프레임씩 수행되도록
		// (1초에 33번 프레임이 돌게 되므로, 33프레임의 게임)
		// (참고로 보통 상용 게임은 Update와 Render의 프레임을 분리하여,
		//  렌더는 60프레임 고정, 업데이트는 수백~수천 프레임으로 돌게 해놓는다.)
		Sleep(30);
	}
}

void GameManager::Update()
{
	// 게임이 가지고 있는 모든 객체들에게 각자 자신을 업데이트 하도록 Update()를 호출
	for (auto& pObject : m_objectList)
	{
		pObject->Update();
	}
}

void GameManager::Render()
{
	// 렌더링을 시작하기 전, 백버퍼를 먼저 깨끗하게 지운다.
	// Q. 안 지우면 이전꺼랑 겹쳐서 나오게 되나요?
    /// > 넵. Clear()를 안하면 이전 프레임에 그려졌던 내용에 추가로 그리게 됩니다.
    /// > 즉, 이전꺼랑 겹쳐서 화면에 표시됩니다.
	auto& console = Console::GetInstance();
	console.Clear();

	// 빈 도화지 상태의 백버퍼에 이번 프레임에 그려질 객체 렌더링 수행
	for (auto& pObject : m_objectList)
	{
		pObject->Render();
	}

	// 모든 객체의 랜더링이 끝나면, 백버퍼와 스크린버퍼를 교체하여
	// 화면에 바뀐 렌더링 내용이 한번에 표시되도록 한다.
	console.SwapBuffer();
}
