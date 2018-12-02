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
    // cmdâ ũ�� ����
    system("mode con: lines=30 cols=90");
    m_ScreenWidth = 90;
    m_ScreenHeight = 30;

    // cmd���� Ŀ�� ���ڰŸ��� ���� �����ϱ� ���� �ɼ� ����
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;

    // 2���� ��ũ�����۸� �����Ͽ� �ʱ�ȭ�Ѵ�. (���� ���۸� ������ ����)
    DWORD accessFlag = GENERIC_READ | GENERIC_WRITE;
    DWORD bufferFlag = CONSOLE_TEXTMODE_BUFFER;
    m_ScreenBuffer[0] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
    m_ScreenBuffer[1] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
    SetConsoleCursorInfo(m_ScreenBuffer[0], &cci);
    SetConsoleCursorInfo(m_ScreenBuffer[1], &cci);

    // 0�� ���۸� Ȱ��ȭ �ϰ�(���� ���̴� ����), ����� �ε����� 1�� �����Ѵ�.(������ �׷��� ����)
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[0]);
    m_BackBufferIdx = 1;
}

void Console::Release()
{
    // ���Ϸ��� ���۴� �ݵ�� �ڵ��� �ݾ��ش�.
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
    // ����۸� Ȱ��ȭ �ϰ�, ����� �ε����� ��ü�Ѵ�.
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
