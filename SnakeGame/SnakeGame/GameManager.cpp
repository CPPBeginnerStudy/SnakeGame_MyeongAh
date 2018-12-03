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
	// Heap 메모리에 New 해준 애들을 Delete 해주는 역할을 하는 곳
	// EX. 게임을 끝내고 메인 화면으로 돌아갔을 때 사용했던 것들을 정리하는 역할
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