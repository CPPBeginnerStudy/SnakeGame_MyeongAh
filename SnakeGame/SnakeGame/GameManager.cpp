#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"
#include "RandomSpeedObj.h"
#include "SnakeHead.h"

// ������, �Ҹ��ڴ� �̹� ������ ������ �־, ��ȯ Ÿ���� �ʿ� ����. (void �̷���)
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
	// ������ OFF�� ����, ���� �����ӿ� ���� �������� ������������ �Ѵ�.
	m_IsOn = false;
}

void GameManager::Init()
{
	Console::GetInstance().Init();
	// ������ ����� ���� �����õ带 �ʱ�ȭ
	// ���� ���� ��, �� �ѹ��� ���־�� �Ѵ�!
	srand((unsigned int)time(nullptr));

	// Console ��ü�� �ν��Ͻ��� �����ͼ� console�̶�� ���������� �����Ͽ� ���
	// �Ź� Console::GetInstance()�� ���ֱ� ���� �̷��� ���������� ����
	// ������ �� ���� ���鿡�� Good
	// auto Ű����� ���ԵǴ� Ÿ�԰� ������ Ÿ������ �ڵ����� �޾��ִ� ����
	auto& console = Console::GetInstance();	//(����) Console& console = Console::GetInstance();
	console.Init();

	// 5���� object�� �����ϸ鼭 �ٿ���� ������ x, y ��ǥ�� �Ź� �����ϰ� ����
	RECT boundaryBox = console.GetBoundaryBox();
	
	// 2���� �⺻ ������Ʈ�� ����
	for (int i = 0; i < 2; i++)
	{
		Object* pObject = new Object();
		pObject->SetShape(L'��'); // wchar_t�� �ٲ�����Ƿ�, L' '�� ����� �Ѵ�.
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		m_ObjectList.push_back(pObject);
	}

	// 3���� Object�� ��ӹ��� RandomSpeedObject��� Ŭ������ ����
	// RandomSpeedObj�� Object�� �ڽ��̱� ������ Object*�� ��� �ڷᱸ���� ���� ���� ����
	for (int i = 0; i < 3; ++i)
	{
		Object* pObject = new Object();
		pObject->SetShape(L'��'); // wchar_t�� �ٲ�����Ƿ�, L' '�� ����� �Ѵ�.
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		m_ObjectList.push_back(pObject);
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

	// ���� ������ ���� �Ӹ��� �����Ѵ�.
	m_pSnakeHead = new SnakeHead();
	m_pSnakeHead->SetShape(L'��');
	m_pSnakeHead->SetX(boundaryBox.right / 2);  // �߾ӿ� ����
	m_pSnakeHead->SetY(boundaryBox.bottom / 2); // �߾ӿ� ����
	m_ObjectList.push_back(m_pSnakeHead);

	// Q. �̻��ϰ�!!!!!!!!!!!!!!! �� �����̴ٰ� �ٸ� ������Ʈ�� ���� �����̴µ�...
	//    �� �׷��� �ɱ��?????????? @_@?????????????

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
	for (auto& pObject : m_ObjectList) // ����� 5�� �������̹Ƿ� 5�� �����
	{
		// pObject->Release(); // ������ ������(pObject)�� ���� Release() ȣ��
		delete pObject; //���� ������ ������(pObject)�� delete �Ͽ� �޸� �Ҵ� ����
		// �ش� �ν��Ͻ��� delete�Ͽ� �޸� �Ҵ� ����
	}

	// �������̴� ��� �����͵��� �� ����Ű�� �ν��Ͻ����� �� �Ҵ� ���������Ƿ�
	// m_ObjectList�� ����ش�. ���ϸ� ���ξ��� �����͵��� ������ �ְ� �ȴ�. (�޸� ��)
	m_ObjectList.clear();
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
	// ���� ���� Ű �Է¿� ���� ó���� �Ѵ�.
	KeyInputHandling();

	// ������ ������ �ִ� ��� ��ü�鿡�� ���� �ڽ��� ������Ʈ �ϵ��� Update()�� ȣ��
	for (auto& pObject : m_ObjectList)
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
	for (auto& pObject : m_ObjectList)
	{
		pObject->Render();
	}

	// ��� ��ü�� �������� ������, ����ۿ� ��ũ�����۸� ��ü�Ͽ�
	// ȭ�鿡 �ٲ� ������ ������ �ѹ��� ǥ�õǵ��� �Ѵ�.
	console.SwapBuffer();
}

void GameManager::KeyInputHandling()
{
	// GetAsyncKeyState()�Լ��� ���� Ű������ Ư�� Ű�� ���� ���¸� ��ȯ�Ѵ�.
	// � Ű�� Ȯ�������� ���ڷ� ������, VK_ �� �����ϴ� ��ũ�ΰ����� �������ִ�.
	// Ű�� ���� ����: https://docs.microsoft.com/ko-kr/windows/desktop/inputdev/virtual-key-codes
	// ��ȯ���� Ű�� ���� ���¿� ���� �÷��װ��̸�, shortŸ��(2byte)���� ���ʳ��� �����ʳ� ��Ʈ�� ��Ʈ�÷��׷� ����Ѵ�.
	// ���� Ű�� �����ִ����� ���ʳ� ��Ʈ�� �˷��ְ�, ������ ������ �־������� �����ʳ� ��Ʈ�� �˷��ش�.
	// ��, �� 4������ ���̽��� �����Ѵ�.
	// 1. 0000 0000 0000 0000 = 0x0000 : ������ ���� ���� ���� ȣ�� �������� �ȴ��� ����
	// 2. 1000 0000 0000 0000 = 0x8000 : ������ ���� ���� ���� ȣ�� �������� ���� ����
	// 3. 0000 0000 0000 0001 = 0x0001 : ������ ���� ���� �ְ� ȣ�� �������� �ȴ��� ����
	// 4. 1000 0000 0000 0001 = 0x8001 : ������ ���� ���� �ְ� ȣ�� �������� ���� ����
	// �̸� ���� Ű�� ���������� ó�� ���ȴ���, �ƴϸ� ������ �ִ� ���¿����� ���� üũ�� �� ������,
	// ��� �Ϲ������� �̷��� ���б����� �ʿ����, Ű�� ���� �����ִ��� ���θ� �˸� �Ǳ� ������
	// �Ʒ��� ���� 0x8000 �÷��װ� �ִ����� ��Ʈ�����Ͽ� Ű�� �������θ� Ȯ���Ѵ�. (��, ���� 2, 4�� ���̽��� ��� trueó��)

	// ESC Ű �Է� ó��
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		// ���α׷� ����
		Shutdown();
	}
	// ESC Ű �Է� ó�� ��

	// ����Ű �Է� ó��
	// else if�� �� �� ������ ���� Ű�� ���� ������ ���� ó�����ֱ� ���ؼ�
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// �� Ű �Է¿� ���� ó���� �� Ŭ������ �ڵ鷯���� �����ϵ��� �Ѱ��ش�.
		// �׷��� ���η����� ��� ������, ���� �۾��ϱ� ��������.
		m_pSnakeHead->OnKeyPress(VK_UP);
		// ���߿� SnakeHead���� Ű�Է��� ���� ����� ����� ���⿡ �߰�
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
	// ����Ű �Է� ó�� ��

	// ������Ű�� �ش� ���� ĳ����(char)�� ����Ʈ���� �����ȴ�.
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		m_pSnakeHead->OnKeyPress('Z');
	}
	if (GetAsyncKeyState('X') & 0x8000)
	{
		m_pSnakeHead->OnKeyPress('X');
	}
	// ������Ű �Է� ó�� ��
}