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

// 이전에 이 함수를 호출했을 때와의 시간 간격을 가져온다.
float Timer::GetDeltaTime()
{
    // 이전 틱과 현재 틱 사이의 시간차를 구하고, 현재 틱을 저장한다. (다음의 계산을 위해)
    TickTime curTick = std::chrono::system_clock::now();
    Seconds deltaTime = curTick - m_PrevTick;
    m_PrevTick = curTick;
    return deltaTime.count();
}

// 특정 시간이 지날 때까지를 체크하기 위한 시간 간격을 설정한다.
void Timer::SetDelay(float _delay)
{
    m_Delay = _delay;
    m_AccumDT = 0.f;
}

// 특정 시간이 지났는지 체크한다.
bool Timer::CheckDelay(float _dt)
{
    // 매 dt를 누적시켜서 일정 시간 이상이 되었는지 체크
    m_AccumDT += _dt;
    if (m_AccumDT < m_Delay)
        return false;

    // 지난 후에는 누적 dt값을 초기화하여 다시 계산할 수 있도록 한다.
    m_AccumDT = 0.f;
    return true;
}
