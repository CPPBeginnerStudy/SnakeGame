#pragma once
class Object;
class SnakeBody;

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

    void                KeyInputHandling();

private:
    bool                m_IsOn;
    std::list<Object*>  m_ObjectList;

    // ���̹� ���� �߿� �����ͺ����� �տ� p�� �ٿ��ִ� ������ �ֽ��ϴ�.
    SnakeBody*          m_pSnakeBody;
};
