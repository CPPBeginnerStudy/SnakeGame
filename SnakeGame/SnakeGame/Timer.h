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

    void        SetDelay(float _delay);
    bool        CheckDelay(float _dt);

private:
    TickTime    m_PrevTick;
    float       m_Delay;
    float       m_AccumDT;
};
