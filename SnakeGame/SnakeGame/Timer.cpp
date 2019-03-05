#include "pch.h"
#include "Timer.h"


Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::Init()
{
	m_PrevTick = std::chrono::system_clock::now();
}

float Timer::GetDeltaTime()
{
	TickTime curTick = std::chrono::system_clock::now();
	Seconds deltaTime = curTick - m_PrevTick;
	m_PrevTick = curTick;

	return deltaTime.count();
	// �෹�̼��� ��ǻ�Ͱ� �����ϴ� �Ǽ���� ���ϴ� �ο� ����
	// ī��Ʈ�� �̷� ��ǻ�� ������ �ð��� �츮�� ���ϴ� �ʴ����� ��ȯ���ִ� ��
}

