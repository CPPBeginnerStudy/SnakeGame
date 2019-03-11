#pragma once
class Object;
class SnakeBody;
class Apple;
class DeathZone;

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

    void                Update(float _dt);
    void                Render();

    void                KeyInputHandling(float _dt);

private:
    bool                m_IsOn;
    std::list<Object*>  m_ObjectList;

    // 네이밍 관습 중에 포인터변수는 앞에 p를 붙여주는 관습이 있습니다.
    SnakeBody*          m_pSnakeBody;
    Apple*              m_pApple;
    DeathZone*          m_pDeathZone;

    float               m_GameSpeed;
};
