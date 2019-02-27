#pragma once
class Timer
{
    using TickTime = std::chrono::system_clock::time_point;
    using Seconds = std::chrono::duration<float>;
public:
    Timer();
    ~Timer();

    void        Init();
    
    float       GetDeltaTime();

    void        SetDelay(float _delayTime);
    bool        CheckDelay();

private:
    TickTime    m_PrevTick;
    TickTime    m_DelayCheckTick;
    float       m_Delay;
};
