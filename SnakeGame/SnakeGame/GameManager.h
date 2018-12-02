#pragma once
class GameManager
{
public:
    static GameManager& GetInstance()
    {
        static GameManager instance;
        return instance;
    }
private:
    GameManager();
    ~GameManager();
public:
    void Run();
    void Shutdown();

private:
    void Init();
    void Release();
    void MainLoop();

private:
    bool m_IsOn;
    int  m_LoopCount;
};
