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
	// ���� ƽ�� ���� ƽ ������ �ð����� ���ϰ�, ���� ƽ�� �����Ѵ�. (������ ����� ����)
	TickTime curTick = std::chrono::system_clock::now();
	Seconds deltaTime = curTick - m_PrevTick;
	m_PrevTick = curTick;
	return deltaTime.count();
	// �෹�̼��� ��ǻ�Ͱ� �����ϴ� �Ǽ���� ���ϴ� �ο� ����
	// ī��Ʈ�� �̷� ��ǻ�� ������ �ð��� �츮�� ���ϴ� �ʴ����� ��ȯ���ִ� ��
}

void Timer::SetDelay(float _delay)
{
	m_Delay = _delay;
	m_AccumDT = 0.f;
}

bool Timer::CheckDelay(float _dt)
{
	// �� dt�� �������Ѽ� ���� �ð� �̻��� �Ǿ����� üũ
	m_AccumDT += _dt;
	if (m_AccumDT < m_Delay)
	{
		return false;
	}

	// ���� �Ŀ��� ���� dt ���� �ʱ�ȭ �Ͽ� �ٽ� ����� �� �ֵ��� �Ѵ�.
	m_AccumDT = 0.f;
	return true;
}

