#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"

// ������, �Ҹ��ڴ� �̹� ������ ������ �־, ��ȯ Ÿ���� �ʿ� ����. (void �̷���)
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
		// [->] �� �ּҿ� �ִ� �༮�� ��� �Լ��� �ҷ��´� (������)
		// [.]�� �ּҸ� �˰� �־ �� �������� ��
		m_objectList.push_back(pObject);
	}
	m_IsOn = true;
}

void GameManager::Release()
{
	// Heap �޸𸮿� New ���� �ֵ��� Delete ���ִ� ������ �ϴ� ��
	// EX. ������ ������ ���� ȭ������ ���ư��� �� ����ߴ� �͵��� �����ϴ� ����

	// �޸� ���� ���̷���, ���� ������Ʈ ���� �س��� �ٷ� ������� �ͼ� delete ���ִ� ���� ����. �� ��԰�
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
		// �� �����Ӹ��� ������Ʈ, ������ ����
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
