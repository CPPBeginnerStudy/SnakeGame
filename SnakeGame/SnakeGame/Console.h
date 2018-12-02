#pragma once
class Console
{
public:
    static Console& GetInstance()
    {
        static Console instance;
        return instance;
    }
private:
    Console();
    ~Console();
public:
    void    Init();
    void    Release();

    void    Clear();
    void    SwapBuffer();

    void    Print(char _shape, short _x, short _y);
    void    PrintText(const std::string& _text, short _x, short _y);

private:
    short   m_ScreenWidth;
    short   m_ScreenHeight;
    HANDLE  m_ScreenBuffer[2];
    short   m_BackBufferIdx;
};
