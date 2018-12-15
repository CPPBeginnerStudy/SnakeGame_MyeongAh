#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"
#include "RandomSpeedObj.h"
#include "SnakeHead.h"

// 생성자, 소멸자는 이미 역할이 정해져 있어서, 반환 타입이 필요 없다. (void 이런거)
GameManager::GameManager()
	: m_IsOn(false)
	, m_pSnakeHead(nullptr)
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
	// 게임 시작 시, 딱 한번만 해주어야 한다!
	srand((unsigned int)time(nullptr));

	// Console 객체의 인스턴스를 가져와서 console이라는 참조변수에 저장하여 사용
	// 매번 Console::GetInstance()를 써주기 보단 이렇게 참조변수를 쓰면
	// 가독성 등 여러 측면에서 Good
	// auto 키워드는 대입되는 타입과 동일한 타입으로 자동으로 받아주는 역할
	auto& console = Console::GetInstance();	//(동일) Console& console = Console::GetInstance();
	console.Init();

	// 5개의 object를 생성하면서 바운더리 내에서 x, y 좌표를 매번 랜덤하게 지정
	RECT boundaryBox = console.GetBoundaryBox();
	
	// 2개는 기본 오브젝트로 생성
	for (int i = 0; i < 2; i++)
	{
		Object* pObject = new Object();
		pObject->SetShape(L'★'); // wchar_t로 바뀌었으므로, L' '로 해줘야 한다.
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		m_ObjectList.push_back(pObject);
	}

	// 3개는 Object를 상속받은 RandomSpeedObject라는 클래스로 생성
	// RandomSpeedObj는 Object의 자식이기 때문에 Object*를 담는 자료구조에 같이 보관 가능
	for (int i = 0; i < 3; ++i)
	{
		Object* pObject = new Object();
		pObject->SetShape(L'♣'); // wchar_t로 바뀌었으므로, L' '로 해줘야 한다.
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		m_ObjectList.push_back(pObject);
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

	// 직접 조종할 뱀의 머리를 생성한다.
	m_pSnakeHead = new SnakeHead();
	m_pSnakeHead->SetShape(L'▣');
	m_pSnakeHead->SetX(boundaryBox.right / 2);  // 중앙에 생성
	m_pSnakeHead->SetY(boundaryBox.bottom / 2); // 중앙에 생성
	m_ObjectList.push_back(m_pSnakeHead);

	// Q. 이상하게!!!!!!!!!!!!!!! 잘 움직이다가 다른 오브젝트랑 같이 움직이는데...
	//    왜 그러는 걸까요?????????? @_@?????????????

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
	for (auto& pObject : m_ObjectList) // 현재는 5개 보관중이므로 5번 실행됨
	{
		// pObject->Release(); // 가져온 데이터(pObject)에 대해 Release() 호출
		delete pObject; //현재 가져온 데이터(pObject)를 delete 하여 메모리 할당 해제
		// 해당 인스턴스를 delete하여 메모리 할당 해제
	}

	// 보관중이던 모든 포인터들이 그 가리키던 인스턴스들을 다 할당 해제했으므로
	// m_ObjectList를 비워준다. 안하면 주인없는 포인터들을 가지고 있게 된다. (메모리 릭)
	m_ObjectList.clear();
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
	// 가장 먼저 키 입력에 대한 처리를 한다.
	KeyInputHandling();

	// 게임이 가지고 있는 모든 객체들에게 각자 자신을 업데이트 하도록 Update()를 호출
	for (auto& pObject : m_ObjectList)
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
	for (auto& pObject : m_ObjectList)
	{
		pObject->Render();
	}

	// 모든 객체의 랜더링이 끝나면, 백버퍼와 스크린버퍼를 교체하여
	// 화면에 바뀐 렌더링 내용이 한번에 표시되도록 한다.
	console.SwapBuffer();
}

void GameManager::KeyInputHandling()
{
	// GetAsyncKeyState()함수는 현재 키보드의 특정 키의 눌린 상태를 반환한다.
	// 어떤 키를 확인할지는 인자로 받으며, VK_ 로 시작하는 매크로값으로 정해져있다.
	// 키값 종류 참고: https://docs.microsoft.com/ko-kr/windows/desktop/inputdev/virtual-key-codes
	// 반환값은 키의 눌린 상태에 대한 플래그값이며, short타입(2byte)에서 왼쪽끝과 오른쪽끝 비트를 비트플래그로 사용한다.
	// 현재 키가 눌려있는지를 왼쪽끝 비트로 알려주고, 이전에 눌린적 있었는지를 오른쪽끝 비트로 알려준다.
	// 즉, 총 4가지의 케이스가 존재한다.
	// 1. 0000 0000 0000 0000 = 0x0000 : 이전에 누른 적이 없고 호출 시점에서 안눌린 상태
	// 2. 1000 0000 0000 0000 = 0x8000 : 이전에 누른 적이 없고 호출 시점에서 눌린 상태
	// 3. 0000 0000 0000 0001 = 0x0001 : 이전에 누른 적이 있고 호출 시점에서 안눌린 상태
	// 4. 1000 0000 0000 0001 = 0x8001 : 이전에 누른 적이 있고 호출 시점에서 눌린 상태
	// 이를 통해 키가 현시점에서 처음 눌렸는지, 아니면 누르고 있는 상태였는지 등을 체크할 수 있지만,
	// 사실 일반적으로 이러한 구분까지는 필요없고, 키가 지금 눌려있는지 여부만 알면 되기 때문에
	// 아래와 같이 0x8000 플래그가 있는지를 비트연산하여 키의 눌림여부를 확인한다. (즉, 위의 2, 4번 케이스를 모두 true처리)

	// ESC 키 입력 처리
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		// 프로그램 종료
		Shutdown();
	}
	// ESC 키 입력 처리 끝

	// 방향키 입력 처리
	// else if로 안 쓴 이유는 여러 키가 같이 눌렸을 때를 처리해주기 위해서
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// 각 키 입력에 대한 처리는 각 클래스의 핸들러에서 구현하도록 넘겨준다.
		// 그래야 메인로직이 깔끔 해지고, 이후 작업하기 편해진다.
		m_pSnakeHead->OnKeyPress(VK_UP);
		// 나중에 SnakeHead말고도 키입력을 받을 대상이 생기면 여기에 추가
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pSnakeHead->OnKeyPress(VK_DOWN);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pSnakeHead->OnKeyPress(VK_LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pSnakeHead->OnKeyPress(VK_RIGHT);
	}
	// 방향키 입력 처리 끝

	// 영문자키는 해당 문자 캐릭터(char)의 바이트값과 대응된다.
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		m_pSnakeHead->OnKeyPress('Z');
	}
	if (GetAsyncKeyState('X') & 0x8000)
	{
		m_pSnakeHead->OnKeyPress('X');
	}
	// 영문자키 입력 처리 끝
}