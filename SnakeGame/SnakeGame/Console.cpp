#include "pch.h"
#include "Console.h"


Console::Console()
    : m_ScreenWidth(0)
    , m_ScreenHeight(0)
    , m_BackBufferIdx(0)
{
    m_ScreenBuffer[0] = nullptr;
    m_ScreenBuffer[1] = nullptr;
}

Console::~Console()
{
}

void Console::Init()
{
    // cmd창 크기 설정
    system("mode con: lines=30 cols=90");
    m_ScreenWidth = 90;
    m_ScreenHeight = 30;

    // cmd에서 커서 깜박거리는 것을 제거하기 위한 옵션 셋팅
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;

    // 2개의 스크린버퍼를 생성하여 초기화한다. (더블 버퍼링 구현을 위해)
    DWORD accessFlag = GENERIC_READ | GENERIC_WRITE;
    DWORD bufferFlag = CONSOLE_TEXTMODE_BUFFER;
    m_ScreenBuffer[0] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
    m_ScreenBuffer[1] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
    SetConsoleCursorInfo(m_ScreenBuffer[0], &cci);
    SetConsoleCursorInfo(m_ScreenBuffer[1], &cci);

    // 0번 버퍼를 활성화 하고(현재 보이는 버퍼), 백버퍼 인덱스를 1로 지정한다.(다음에 그려질 버퍼)
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[0]);
    m_BackBufferIdx = 1;
}

void Console::Release()
{
    // 사용완료한 버퍼는 반드시 핸들을 닫아준다.
    CloseHandle(m_ScreenBuffer[0]);
    CloseHandle(m_ScreenBuffer[1]);
}

void Console::Clear()
{
    DWORD dw;
    DWORD screenSize = m_ScreenWidth * m_ScreenHeight;
    FillConsoleOutputCharacter(m_ScreenBuffer[m_BackBufferIdx], ' ', screenSize, { 0, 0 }, &dw);
}

void Console::SwapBuffer()
{
    // 백버퍼를 활성화 하고, 백버퍼 인덱스를 교체한다.
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_BackBufferIdx]);
    switch (m_BackBufferIdx)
    {
    case 0: m_BackBufferIdx = 1; break;
    case 1: m_BackBufferIdx = 0; break;
    }
}   

void Console::Print(char _shape, short _x, short _y)
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
    WriteConsole(m_ScreenBuffer[m_BackBufferIdx], &_shape, 1, &dw, nullptr);
}

void Console::PrintText(const std::string& _text, short _x, short _y)
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
    WriteConsole(m_ScreenBuffer[m_BackBufferIdx], _text.c_str(), _text.length(), &dw, nullptr);
}
