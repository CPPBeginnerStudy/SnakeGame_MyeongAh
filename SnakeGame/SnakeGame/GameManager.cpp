#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"
#include "RandomSpeedObj.h"
#include "SnakeHead.h"
#include "Apple.h"
#include "Timer.h"
#include "DeathZone.h"

// 생성자, 소멸자는 이미 역할이 정해져 있어서, 반환 타입이 필요 없다. (void 이런거)
GameManager::GameManager()
	: m_IsRunning(false)
	, m_IsPlaying(false)
	, m_pSnakeHead(nullptr)
	, m_pApple(nullptr)
	, m_pDeathZone(nullptr)
	, m_GameSpeed(1.f)
	, m_GameLevel(1)
	, m_GameScore(0)
	, m_EatAppleNum(0)
	, m_GoalAppleNum(10)
{
}

GameManager::~GameManager()
{
}

void GameManager::Run()
{
	m_IsRunning = true;

	// 게임 오버가 되어도 처음으로 돌아가 게임을 다시 시작할 수 있도록 해주기 위한 메인 루프
	// 이 루프를 빠져나가야 비로소 프로그램이 종료된다.
	while (m_IsRunning)
	{
		Init();
		GameLoop();
		Release();
	}
}

void GameManager::Shutdown()
{
	// 게임을 OFF로 만들어서, 다음 프레임에 메인 루프에서 빠져나오도록 한다.
	m_IsRunning = false;
	m_IsPlaying = false;
}

void GameManager::GameOver()
{
	// 플레이 플래그를 off 하여 게임 루프를 빠져나오게 한다.
	m_IsPlaying = false;
}

int GameManager::GetRandom(int _min, int _max) const
{
	// 최소, 최대 범위를 지정하여 랜덤값을 산출하는 함수
	int range = _max - _min;
	if (range < 1)
	{
		// 최소한 min ~ max 값의 차이가 1 이상은 나야 의미가 있으니 나머진 예외 처리한다.
		return 0;
	}
	int result = rand() % (range + 1); // 범위값으로 나눈 나머지 값. 0 ~ range 사이의 랜덤값
	return result + _min; // 결과값에 min값을 더해주어야 비로소 min ~ max 사이의 랜덤값이 됨
}

void GameManager::OnAppleEaten()
{
	// 사과 먹을 때마다 현재 난이도만큼 점수 올려주기
	m_GameScore += m_GameLevel;

	// 목표 개수만큼 사과를 먹으면 게임 레벨 변경
	m_EatAppleNum++;
	if (m_EatAppleNum >= m_GoalAppleNum)
	{
		GoToNextStage();
	}
}

void GameManager::Init()
{
	// 랜덤값 사용을 위해 랜덤시드를 초기화
	// 게임 시작 시, 딱 한번만 해주어야 한다!
	// 이 랜덤 시드를 기반으로 앞으로 랜덤 값을 산출하게 된다.
	srand((unsigned int)time(nullptr));

	// Console 객체의 인스턴스를 가져와서 console이라는 참조변수에 저장하여 사용
	// 매번 Console::GetInstance()를 써주기 보단 이렇게 참조변수를 쓰면
	// 가독성 등 여러 측면에서 Good
	// auto 키워드는 대입되는 타입과 동일한 타입으로 자동으로 받아주는 역할
	auto& console = Console::GetInstance();	//(동일) Console& console = Console::GetInstance();
	console.Init();

	// 동일한 길이에 대해 인게임 좌표보다 cmd 좌표가 x값이 2배이기 때문에 2로 나눠준다.
	RECT boundaryBox = console.GetBoundaryBox();
	//boundaryBox.right /= 2;

	// RandomSpeedObj는 Object를 상속받은 자식이기 때문에 Object*를 담는 자료구조에 같이 보관 가능
	// RandomSpeedObj를 생성하면서 x, y 좌표를 바운더리 내에서 매번 랜덤하게 지정한다.
	//for (int i = 0; i < 3; ++i)
//	{
        /// > 아래에서 RandomSpeedObj()가 아니라 Object()로 생성하고 있네요;ㅁ;
		// 아앗! 복붙하다가 바뀐것 같습니당 @_@ 바꾸어 놓을게여!!
//		Object* pObject = new RandomSpeedObj();
		//pObject->SetShape(L'♣'); // wchar_t로 바뀌었으므로, L' '로 해줘야 한다.
//		pObject->SetX(rand() % boundaryBox.right);
//		pObject->SetY(rand() % boundaryBox.bottom);
//		m_ObjectList.push_back(pObject);
//	}
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
	//m_pSnakeHead->SetShape(L'▣');
	m_pSnakeHead->SetX(boundaryBox.right / 2);  // 중앙에 생성
	m_pSnakeHead->SetY(boundaryBox.bottom / 2); // 중앙에 생성
	m_ObjectList.push_back(m_pSnakeHead);
	// cmd 좌표계에서 한글은 가로 2칸씩 차지, 세로는 1칸씩
	// 그래서 넘겨줄 때 2를 곱해서 넘겨주고 그런당 >> 정수 좌표계를 쓰도록 바꿔서 이제는 딱 1칸씩만 움직여 보이도록 바뀌었음

	// Q. 이상하게!!!!!!!!!!!!!!! 잘 움직이다가 다른 오브젝트랑 같이 움직이는데...
	//    왜 그러는 걸까요?????????? @_@?????????????
    /// > 요것은.. 빌드해서 테스트해봐도 재현이 안되는 군요...@_@
    /// > 보통 객체의 좌표가 cmd창의 범위를 벗어나면 그런 현상이 발생하는데..
    /// > 지금 코드에선 문제없는 듯 한데.. 혹시 재현이 되고 계신다면 재현스텝을...알려주세요ㅋㅋ
	// 제 컴퓨터가 이상한 걸까요.........? ㅎㅎㅎㅎㅎㅎ

	// 뱀이 먹을 사과를 생성한다.
	m_pApple = new Apple();
//	m_pApple->SetX(rand() % (boundaryBox.right - 2) + 1); // 벽 있으니까, 벽 안쪽에 사과가 생기도록.
//	m_pApple->SetY(rand() % (boundaryBox.bottom -2) + 1);
	m_pApple->RandomMovePosition();
	m_ObjectList.push_back(m_pApple);
	
	// 데스존을 생성한다.
	m_pDeathZone = new DeathZone();
	m_pDeathZone->GenerateLines();
	m_ObjectList.push_back(m_pDeathZone);

	// 모든 초기화 완료 되었으므로 게임 상태를 플레이 중으로 설정
	m_IsPlaying = true;
	m_GameSpeed = 1.f;
	m_GameLevel = 1;
	m_GameScore = 0;
	m_EatAppleNum = 0;
	m_GoalAppleNum = 10;
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
	m_pSnakeHead = nullptr;
	m_pApple = nullptr;
	m_pDeathZone = nullptr;
}

void GameManager::GameLoop()
{
	Timer mainTimer;
	Timer updateTimer;
	Timer renderTimer;
	updateTimer.SetDelay(0.1f); // 1초에 10번 업데이트 되도록
	renderTimer.SetDelay(0.05f); // 1초에 20번 렌더링 되도록

	while (m_IsPlaying)
	{
		float realDT = mainTimer.GetDeltaTime(); //이루프와 다음루프 사이의 시간 간격을 알 수 있음 씨피유에서 계산하다보면 이러한 시간 간격이 조금씩 달라질 수 있기 때문에
		float gameDT = realDT * m_GameSpeed;
		// 델타 타임을 곱해줌으로써 이번 루프와 저번루프 사이의 간격을 알게 되어서 그만큼 보정해줄 수 있음
		// 1초에 1만큼 이동한다를 보장해줄 수 있음
		// 한 프레임마다 업데이트, 랜더링 진행
		// 1초에 3프레임짜리 게임이 있고, 프레임 간격이 불규칙할 때, 그 것이 의도대로 움직이도록 보장
		// 막 게임 랙 걸렸는데 멈췄다가 다시 되돌아오니 저만큼 가 있는 것

		// 게임의 업데이트는 게임 스피드가 적용된 dt를 넘겨서 스피드 조절이 가능하게 한다.
		if (updateTimer.CheckDelay(gameDT))
		{
			Update(gameDT);
		}

		// 렌더 프레임 제한은 실제 dt로 체크한다. (게임 속도와 무관하게)
		if (renderTimer.CheckDelay(realDT))
		{
			// 렌더링 프레임이 너무 빠르면 오히려 화면이 버벅인다.
			// Update와 다르게 눈이 편한 정도로 제한을 두는 것이 좋다.
			Render();
		}

		// Sleep()함수는 인자로 받은 수치만큼(밀리세컨드 단위) 프로그램을 정지시킨다.
		// 메인 루프가 너무 빨리 돌면 화면을 알아보기 힘들기 때문에, 0.03초마다 한 프레임씩 수행되도록
		// (1초에 33번 프레임이 돌게 되므로, 33프레임의 게임)
		// (참고로 보통 상용 게임은 Update와 Render의 프레임을 분리하여,
		//  렌더는 60프레임 고정, 업데이트는 수백~수천 프레임으로 돌게 해놓는다.)
		
		// Sleep(30 / m_GameSpeed); //_dt만들면서 다르게 사용할 예쩡
		// 단점: 매우 빠르게 하면 정확하게 시간이 변하지 않을 수 있음
		// 상용 게임에선 일케 안 함!! 게임 타이머를 따로 만들어서 함
	}

	// 게임이 종료되었을 때, 표시할 여러 가지들을 아래 함수에서 처리
	ShowGameOverState();
}

void GameManager::Update(float _dt)
{
	// 업데이트에서는 항상 델타타임을 사용함

	// 가장 먼저 키 입력에 대한 처리를 한다.
	KeyInputHandling();

	// 게임이 가지고 있는 모든 객체들에게 각자 자신을 업데이트 하도록 Update()를 호출
	for (auto& pObject : m_ObjectList)
	{
		pObject->Update(_dt);
	}

	// 충돌 처리는 OnHit으로 묶어서 각각 처리할 수 있을 듯 - 고쳐보자!!
	// 뱀이 사과를 먹으면 뱀에 꼬리를 추가해주고 사과를 다른 곳으로 옮긴다.
	/*
	if (m_pSnakeHead->GetX() > m_pApple->GetX() - 0.5f &&
		m_pSnakeHead->GetX() < m_pApple->GetX() + 0.5f &&
		m_pSnakeHead->GetY() > m_pApple->GetY() - 0.5f &&
		m_pSnakeHead->GetY() < m_pApple->GetY() + 0.5f)
	{
		m_pSnakeHead->AddTail();

		RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
		boundaryBox.right /= 2;
		m_pApple->SetX(rand() % boundaryBox.right);
		m_pApple->SetY(rand() % boundaryBox.bottom);
	}
	

	if (m_pSnakeHead->GetX() == m_pApple->GetX() &&
		m_pSnakeHead->GetY() == m_pApple->GetY())
	{
		// 사과 먹을 때마다 현재 난이도만큼의 점수 부여
		m_GameScore += m_GameLevel;

		// 목표 개수만큼 사과를 먹으면 게임 레벨 변경
		m_EatAppleNum++;
		if (m_EatAppleNum >= m_GoalAppleNum)
		{
			GoToNextStage();
		}
		m_pSnakeHead->AddTail();

//		RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
//		m_pApple->SetX(rand() % (boundaryBox.right - 2) + 1);
//		m_pApple->SetY(rand() % (boundaryBox.bottom - 2) + 1);
		m_pApple->RandomMovePosition();
	}
	
	// 뱀이 데스존에 들어가면 게임 오버
	if (m_pDeathZone->IsInDeathZone(m_pSnakeHead))
	{
		GameManager::GetInstance().GameOver();
	}
	*/

	// 모든 객체들이 업데이트 완료된 후에 충돌 체크 처리
	CollisionCheck();
}

void GameManager::Render()
{
	// 렌더링을 시작하기 전, 백버퍼를 먼저 깨끗하게 지운다.
	// Q. 안 지우면 이전꺼랑 겹쳐서 나오게 되나요?
    /// > 넵. Clear()를 안하면 이전 프레임에 그려졌던 내용에 추가로 그리게 됩니다.
    /// > 즉, 이전꺼랑 겹쳐서 화면에 표시됩니다.
	Console::GetInstance().Clear();

	// 빈 도화지 상태의 백버퍼에 이번 프레임에 그려질 객체 렌더링 수행
	for (auto& pObject : m_ObjectList)
	{
		pObject->Render();
	}

	// 화면 맨 아래 빈 공간에 게임 상태 관련 텍스트 출력
	/*
	RECT boundaryBox = console.GetBoundaryBox();
	std::wostringstream oss;
	oss << L"GameSpeed: " << m_GameSpeed << L"\t"
		<< L"GameLevel: " << m_GameLevel << L"\t"
		<< L"GameScore: " << m_GameScore << L"\t"
		<< L"Eat Apple: " << m_EatAppleNum << L"/" << m_GoalAppleNum;
	console.PrintText(oss.str(), boundaryBox.left, boundaryBox.bottom + 1);
	*/
	PrintGameState();

	// 모든 객체의 랜더링이 끝나면, 백버퍼와 스크린버퍼를 교체하여
	// 화면에 바뀐 렌더링 내용이 한번에 표시되도록 한다.
	Console::GetInstance().SwapBuffer();
}

void GameManager::KeyInputHandling()
{
	// 키입력에 대한 세부구현은 아래 함수에서 처리하도록 구현을 분리하고,
	// 여기서는 각 키가 눌렸을 때 게임 매니저가 해야할 동작들에 집중한다.
	if (CheckKeyInput(VK_ESCAPE))
	{
		// ESC 키가 눌리면 프로그램 종료
		Shutdown();
		return;
	}

	// 방향키 입력은 동시에 멀티입력이 되면 안 된다.
	if (CheckKeyInput(VK_UP)) {}
	else if (CheckKeyInput(VK_DOWN)) {}
	else if (CheckKeyInput(VK_LEFT)) {}
	else if (CheckKeyInput(VK_RIGHT)) {}

	// 그외 입력 처리 (else if가 아닌 이유는, 여러 키가 같이 눌렸을때에 모두 처리해줘야하기 때문)
	// 영문자키는 해당 문자 캐릭터(char)의 바이트값과 대응된다.
	if (CheckKeyInput('Z'))
	{
		// 게임 속도 줄이기 (최소 0.5배)
		m_GameSpeed = std::max<float>(m_GameSpeed - 0.1f, 0.5f);
	}
	if (CheckKeyInput('X'))
	{
		// 게임 속도 늘리기 (최대 2배)
		m_GameSpeed = std::min<float>(m_GameSpeed + 0.1f, 2.f);
	}
}

bool GameManager::CheckKeyInput(int _keyIdx)
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
	if (GetAsyncKeyState(_keyIdx) & 0x8000)
	{
		//Shutdown(); // 프로그램 종료
//	}
	// ESC 키 입력 처리 끝

	/*
	// 방향키 입력 처리
	// 동시 입력이 되면 안되므로 else if로 처리해야 함
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// 각 키 입력에 대한 처리는 각 클래스의 핸들러에서 구현하도록 넘겨준다.
		// 그래야 메인로직이 깔끔 해지고, 이후 작업하기 편해진다.
		m_pSnakeHead->OnKeyPress(_keyIdx);
		// 나중에 SnakeHead말고도 키입력을 받을 대상이 생기면 여기에 추가
		return true;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pSnakeHead->OnKeyPress(VK_DOWN);
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pSnakeHead->OnKeyPress(VK_LEFT);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pSnakeHead->OnKeyPress(VK_RIGHT);
	}
	// 방향키 입력 처리 끝

	// 영문자키는 해당 문자 캐릭터(char)의 바이트값과 대응된다.
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		m_pSnakeHead->OnKeyPress('Z');
		// 게임 속도 줄이기 (최소 0.5배)
		m_GameSpeed = std::max<float>(m_GameSpeed - 0.1f, 0.5f);
	}
	if (GetAsyncKeyState('X') & 0x8000)
	{
		m_pSnakeHead->OnKeyPress('X');
		// 게임 속도 늘리기 (최대 2배)
		m_GameSpeed = std::min<float>(m_GameSpeed + 0.1f, 2.f);
	}
	// 영문자키 입력 처리 끝
	*/

	// 키 입력에 대한 처리는 각 클래스의 핸들러에서 구현하도록 넘겨준다.
	// 그래야 메인 로직이 간결해지고, 이후 작업이 편해진다.
		m_pSnakeHead->OnKeyPress(_keyIdx);

		// 나중에 SnakeHead 이외에 키입력 받을 대상이 생기면 여기에 추가
		return true;
	}
	return false;
}

void GameManager::PrintGameState()
{
	// 화면 최하단의 빈 공간에 게임 상태 관련 텍스트들을 출력
	auto& console = Console::GetInstance();
	RECT boundaryBox = console.GetBoundaryBox();
	std::wostringstream oss;
	oss << L"GameSpeed: " << m_GameSpeed << L"\t"
		<< L"GameLevel: " << m_GameLevel << L"\t"
		<< L"GameScore: " << m_GameScore << L"\t"
		<< L"Eat Apple: " << m_EatAppleNum << L"/" << m_GoalAppleNum;
	console.PrintText(oss.str(), (short)boundaryBox.left, (short)boundaryBox.bottom + 1);
}

void GameManager::ShowGameOverState()
{
	// 결과 화면  - 더이상 렌더링 루프에 들어가지 않으므로 직접 스왑 버퍼 처리까지 해준다.
	auto& console = Console::GetInstance();
	console.Clear();

	RECT boundaryBox = console.GetBoundaryBox();
	
	std::wostringstream oss;
	oss << L"\t\t\t\t    --- GameOver ---\n\n"
		<< L"\t\t\t\t     Score:   " << m_GameScore << L"\n"
		<< L"\t\t\t\t     Restart: ENTER\n"
		<< L"\t\t\t\t     Exit:    ESC";
	console.PrintText(oss.str(), (short)boundaryBox.left, (short)(boundaryBox.bottom / 2.3f));
	console.SwapBuffer();

	// 유저 입력 대기
	while (_getch())
	{
		if (CheckKeyInput(VK_ESCAPE))
		{
			Shutdown(); // ESC 누르면 게임 종료
			return;
		}
		if (CheckKeyInput(VK_RETURN)) return;
		// Q. 처음 죽고 나서는 다시 시작이 되는데, 한번 더 죽으면 다시 시작이 안 돼요... 왜일까요...?
	}
}

void GameManager::GoToNextStage()
{
	m_GameScore += m_GameLevel * 10; // 스테이지 클리어할 때마다 [현재 스태이미 * 10]만큼의 보너스 점수
	m_GameLevel++;
	m_GoalAppleNum += 10 + m_GameLevel * 2; // 다음 목표는 10 + 레벨*2
}

void GameManager::CollisionCheck()
{
	// 충돌체가 2개 이상이 존재하는 경우만 충돌체크가 의미있다.
	if (m_ObjectList.size() < 2) return;

	for (auto& pObject : m_ObjectList)
	{
		for (auto& pObjectOther : m_ObjectList)
		{
			// 충돌한 경우 상대에게 내가 쳤다고 알려준다.
			if (pObject->HitCheck(pObjectOther))
			{
				pObjectOther->OnHit(pObject);
			}
		}
	}
}
