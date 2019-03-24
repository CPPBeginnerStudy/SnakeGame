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
    void                GameOver();

    int                 GetRandom(int _min, int _max) const;
    int                 GetGameLevel() const { return m_GameLevel; }

    void                OnAppleEaten();

private:
    void                Init();
    void                Release();
    void                GameLoop();

    void                Update(float _dt);
    void                Render();

    void                KeyInputHandling();
    bool                CheckKeyInput(int _keyIdx);

    void                PrintGameState();
    void                ShowGameOverState();
    void                GoToNextStage();
    void                CollisionCheck();

private:
    bool                m_IsRunning;
    bool                m_IsPlaying;
    std::list<Object*>  m_ObjectList;

    // 네이밍 관습 중에 포인터변수는 앞에 p를 붙여주는 관습이 있습니다.
    SnakeBody*          m_pSnakeBody;
    Apple*              m_pApple;
    DeathZone*          m_pDeathZone;

    float               m_GameSpeed;
    int                 m_GameLevel;
    int                 m_GameScore;
    int                 m_EatAppleNum;
    int                 m_GoalAppleNum;
};
