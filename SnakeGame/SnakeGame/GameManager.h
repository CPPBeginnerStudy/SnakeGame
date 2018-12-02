#pragma once
class Object;

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
    void                Run();
    void                Shutdown();

private:
    void                Init();
    void                Release();
    void                MainLoop();

    void                Update();
    void                Render();

private:
    bool                m_IsOn;
    std::list<Object*>  m_ObjectList;
};
