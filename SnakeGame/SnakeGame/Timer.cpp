#include "pch.h"
#include "Timer.h"


Timer::Timer()
{
	Init();
}


Timer::~Timer()
{
}

void Timer::Init()
{
	m_PrevTick = std::chrono::system_clock::now();
	m_Delay = 0.f;
	m_AccumDT = 0.f;
}

float Timer::GetDeltaTime()
{
	// 이전 틱과 현재 틱 사이의 시간차를 구하고, 현재 틱을 저장한다. (다음의 계산을 위해)
	TickTime curTick = std::chrono::system_clock::now();
	Seconds deltaTime = curTick - m_PrevTick;
	m_PrevTick = curTick;
	return deltaTime.count();
	// 듀레이션은 컴퓨터가 좋아하는 실수계산 안하는 로우 숫자
	// 카운트는 이런 컴퓨터 단위의 시간을 우리가 원하는 초단위로 변환해주는 것
}

void Timer::SetDelay(float _delay)
{
	m_Delay = _delay;
	m_AccumDT = 0.f;
}

bool Timer::CheckDelay(float _dt)
{
	// 매 dt를 누적시켜서 일정 시간 이상이 되었는지 체크
	m_AccumDT += _dt;
	if (m_AccumDT < m_Delay)
	{
		return false;
	}

	// 지난 후에는 누적 dt 값을 초기화 하여 다시 계산할 수 있도록 한다.
	m_AccumDT = 0.f;
	return true;
}

