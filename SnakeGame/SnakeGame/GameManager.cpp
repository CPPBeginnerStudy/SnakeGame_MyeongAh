#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"

// 생성자, 소멸자는 이미 역할이 정해져 있어서, 반환 타입이 필요 없다. (void 이런거)
GameManager::GameManager()
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
	m_IsOn = false;
}

void GameManager::Init()
{
	for (int i = 0; i < 5; i++)
	{
		Object* pObject = new Object();
		pObject->Init();
		// [->] 그 주소에 있는 녀석의 멤버 함수를 불러온다 (포인터)
		// [.]은 주소를 알고 있어서 걍 가져오는 것
		m_objectList.push_back(pObject);
	}
	m_IsOn = true;
}

void GameManager::Release()
{
	// Heap 메모리에 New 해준 애들을 Delete 해주는 역할을 하는 곳
	// EX. 게임을 끝내고 메인 화면으로 돌아갔을 때 사용했던 것들을 정리하는 역할

	// 메모리 릭을 줄이려면, 뭔가 오브젝트 만들어서 해놓고 바로 릴리즈로 와서 delete 해주는 것이 좋음. 안 까먹게
	for (auto& pObject : m_objectList)
	{
		pObject->Release();
		delete pObject;
	}
}

void GameManager::MainLoop()
{
	int loopCount = 0;
	while (m_IsOn)
	{
		// 한 프레임마다 업데이트, 랜더링 진행
		Update();
		Render();
	}
}

void GameManager::Update()
{
	for (auto& pObject : m_objectList)
	{
		pObject->Update();
	}
}

void GameManager::Render()
{
	for (auto& pObject : m_objectList)
	{
		pObject->Render();
	}
}
