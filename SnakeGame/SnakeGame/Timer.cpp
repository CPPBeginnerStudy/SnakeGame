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
void Timer::SetDelay(float _delayTime)
{
    m_Delay = _delayTime;
    m_DelayCheckTick = std::chrono::system_clock::now();
}

// 특정 시간이 지났는지 체크한다.
bool Timer::CheckDelay()
{
    TickTime curTick = std::chrono::system_clock::now();
    Seconds deltaTime = curTick - m_DelayCheckTick;
    if (deltaTime.count() < m_Delay)
        return false;

    // 지난 후에는 다시 현재 시간부터 특정 시간을 체크하도록 갱신한다.
    m_DelayCheckTick = curTick;
    return true;
}
