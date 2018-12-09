#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"

// ������, �Ҹ��ڴ� �̹� ������ ������ �־, ��ȯ Ÿ���� �ʿ� ����. (void �̷���)
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
	// ������ OFF�� ����, ���� �����ӿ� ���� �������� ������������ �Ѵ�.
	m_IsOn = false;
}

void GameManager::Init()
{
	Console::GetInstance().Init();
	// ������ ����� ���� �����õ带 �ʱ�ȭ
	srand((unsigned int)time(nullptr));

	// Console ��ü�� �ν��Ͻ��� �����ͼ� console�̶�� ���������� �����Ͽ� ���
	// �Ź� Console::GetInstance()�� ���ֱ� ���� �̷��� ���������� ����
	// ������ �� ���� ���鿡�� Good
	// auto Ű����� ���ԵǴ� Ÿ�԰� ������ Ÿ������ �ڵ����� �޾��ִ� ����
	auto& console = Console::GetInstance();	//(����) Console& console = Console::GetInstance();
	console.Init();

	// 5���� object�� �����ϸ鼭 �ٿ���� ������ x, y ��ǥ�� �Ź� �����ϰ� ����
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
		// [->] �� �ּҿ� �ִ� �༮�� ��� �Լ��� �ҷ��´� (������)
		// [.]�� �ּҸ� �˰� �־ �� �������� ��
		m_objectList.push_back(pObject);
	}
	*/
	// ��� �ʱ�ȭ �Ϸ� �Ǿ����Ƿ� ���� ON
	m_IsOn = true;
}

void GameManager::Release()
{
	// ���� ���Ӱ� ���õ� ��� ��ü���� Release
	// ������ Init()���� �ʱ�ȭ ���� ��ü���� ���⼭ Release ���ָ� ��
	// Heap �޸𸮿� New ���� �ֵ��� Delete ���ִ� ������ �ϴ� ��
	// EX. ������ ������ ���� ȭ������ ���ư��� �� ����ߴ� �͵��� �����ϴ� ����
	Console::GetInstance().Release();

	// �޸� ���� ���̷���, ���� ������Ʈ ���� �س��� �ٷ� ������� �ͼ� delete ���ִ� ���� ����. �� ��԰�
	// m_ObjectList��� �ڷᱸ������ �� ����� �����͸� ����ȸ�ŭ �ϳ��� �������� �ݺ���
	for (auto& pObject : m_objectList) // ����� 5�� �������̹Ƿ� 5�� �����
	{
		pObject->Release(); // ������ ������(pObject)�� ���� Release() ȣ��
		delete pObject;     // �ش� �ν��Ͻ��� delete�Ͽ� �޸� �Ҵ� ����
	}

	// �������̴� ��� �����͵��� �� ����Ű�� �ν��Ͻ����� �� �Ҵ� ���������Ƿ�
	// m_ObjectList�� ����ش�. ���ϸ� ���ξ��� �����͵��� ������ �ְ� �ȴ�. (�޸� ��)
	m_objectList.clear();
}

void GameManager::MainLoop()
{
	while (m_IsOn)
	{
		// �� �����Ӹ��� ������Ʈ, ������ ����
		Update();
		Render();

		// Sleep()�Լ��� ���ڷ� ���� ��ġ��ŭ(�и������� ����) ���α׷��� ������Ų��.
		// ���� ������ �ʹ� ���� ���� ȭ���� �˾ƺ��� ����� ������, 0.03�ʸ��� �� �����Ӿ� ����ǵ���
		// (1�ʿ� 33�� �������� ���� �ǹǷ�, 33�������� ����)
		// (����� ���� ��� ������ Update�� Render�� �������� �и��Ͽ�,
		//  ������ 60������ ����, ������Ʈ�� ����~��õ ���������� ���� �س��´�.)
		Sleep(30);
	}
}

void GameManager::Update()
{
	// ������ ������ �ִ� ��� ��ü�鿡�� ���� �ڽ��� ������Ʈ �ϵ��� Update()�� ȣ��
	for (auto& pObject : m_objectList)
	{
		pObject->Update();
	}
}

void GameManager::Render()
{
	// �������� �����ϱ� ��, ����۸� ���� �����ϰ� �����.
	// Q. �� ����� �������� ���ļ� ������ �ǳ���?
    /// > ��. Clear()�� ���ϸ� ���� �����ӿ� �׷����� ���뿡 �߰��� �׸��� �˴ϴ�.
    /// > ��, �������� ���ļ� ȭ�鿡 ǥ�õ˴ϴ�.
	auto& console = Console::GetInstance();
	console.Clear();

	// �� ��ȭ�� ������ ����ۿ� �̹� �����ӿ� �׷��� ��ü ������ ����
	for (auto& pObject : m_objectList)
	{
		pObject->Render();
	}

	// ��� ��ü�� �������� ������, ����ۿ� ��ũ�����۸� ��ü�Ͽ�
	// ȭ�鿡 �ٲ� ������ ������ �ѹ��� ǥ�õǵ��� �Ѵ�.
	console.SwapBuffer();
}
