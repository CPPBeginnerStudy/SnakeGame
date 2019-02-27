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
	m_DelayCheckTick = std::chrono::system_clock::now();
	m_Delay = 0.f;
}

// ������ �� �Լ��� ȣ������ ������ �ð� ������ �����´�.
float Timer::GetDeltaTime()
{
	// ���� ƽ�� ���� ƽ ������ �ð����� ���ϰ�, ���� ƽ�� �����Ѵ�. (������ ����� ����)
	TickTime curTick = std::chrono::system_clock::now();
	Seconds deltaTime = curTick - m_PrevTick;
	m_PrevTick = curTick;
	return deltaTime.count();
}

// Ư�� �ð��� ���� �������� üũ�ϱ� ���� �ð� ������ �����Ѵ�.
void Timer::SetDelay(float _delayTime)
{
	m_Delay = _delayTime;
	m_DelayCheckTick = std::chrono::system_clock::now();
}

// Ư�� �ð��� �������� üũ�Ѵ�.
bool Timer::CheckDelay()
{
	TickTime curTick = std::chrono::system_clock::now();
	Seconds deltaTime = curTick - m_DelayCheckTick;
	if (deltaTime.count() < m_Delay)
		return false;

	// ���� �Ŀ��� �ٽ� ���� �ð����� Ư�� �ð��� üũ�ϵ��� �����Ѵ�.
	m_DelayCheckTick = curTick;
	return true;
}
