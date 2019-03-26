#pragma once
class Timer
{
	using TickTime = std::chrono::system_clock::time_point;
	using Seconds = std::chrono::duration<float>; // 1초를 무엇으로 표현할 것인가 디폴트가 1초임 밀리세컨 일케 바꿀 수도 있음

public:
	Timer();
	~Timer();

	void Init();
	float GetDeltaTime();

	void SetDelay(float _delay);
	bool CheckDelay(float _dt);

private:
	TickTime m_PrevTick;
	float m_Delay;
	float m_AccumDT;
};
