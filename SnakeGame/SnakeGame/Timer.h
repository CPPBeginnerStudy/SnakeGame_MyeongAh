#pragma once
class Timer
{
	using TickTime = std::chrono::system_clock::time_point;
	using Seconds = std::chrono::duration<float>; // 1�ʸ� �������� ǥ���� ���ΰ� ����Ʈ�� 1���� �и����� ���� �ٲ� ���� ����

public:
	Timer();
	~Timer();

	void Init();
	float GetDeltaTime();

private:
	TickTime m_PrevTick;
};

