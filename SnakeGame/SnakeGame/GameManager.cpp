#include "pch.h"
#include "GameManager.h"

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
	m_IsOn = true;
}

void GameManager::Release()
{
	// Heap �޸𸮿� New ���� �ֵ��� Delete ���ִ� ������ �ϴ� ��
	// EX. ������ ������ ���� ȭ������ ���ư��� �� ����ߴ� �͵��� �����ϴ� ����
}

void GameManager::MainLoop()
{
	int loopCount = 0;
	while (m_IsOn)
	{
		if (++loopCount > 10)
		{
			Shutdown();
		}
		std::cout << "Hello World!\n";
	}
}