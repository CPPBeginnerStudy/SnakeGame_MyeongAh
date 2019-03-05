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
	// 듀레이션은 컴퓨터가 좋아하는 실수계산 안하는 로우 숫자
	// 카운트는 이런 컴퓨터 단위의 시간을 우리가 원하는 초단위로 변환해주는 것
}

