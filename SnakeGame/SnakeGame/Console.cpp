#include "pch.h"
#include "Console.h"


// �⺻������ Ŭ������ ��� ��������� �����ڿ��� �Ʒ��� ���� �ʱ�ȭ���־�� �Ѵ�.
// �׷��� ������ ���� ���Ե��� ���� ���·� ����� ������ �ְ�,
// �׷� ��� '�����Ⱚ'�̶�� �Ҹ��� ���������� ������ ���� �� �ֱ� �����̴�.
Console::Console()
    : m_ScreenWidth(0)      // ù��° ������ : ������
    , m_ScreenHeight(0)     // �������ʹ� , ������ ����.
    , m_BackBufferIdx(0)    // () �ȿ� �ʱ�ȭ�� ���� �ִ´�.
{
    // ��������� �迭�� ��� ������ �ʱ�ȭ ���� �ʰ�,
    // �Ʒ��� ���� �� �迭 �׸���� ���� �ʱ�ȭ���־�� �Ѵ�.
    // nullptr�̶�, �����ͺ����� ���� ���ΰ��̶�� ���� �Ǹ�,
    // �Ʒ� ������ Ÿ���� HANDLE Ÿ��������, ������ � ��ü�� ������ Ÿ���̴�.
    // ��, HANDLE Ÿ���� ������ Ÿ��.
    m_ScreenBuffer[0] = nullptr;
    m_ScreenBuffer[1] = nullptr;
}

Console::~Console()
{
}

void Console::Init()
{
    // cmdâ ũ�� ���� (30���� ��(����), 90���� �÷�(����))
    // cmd���� ���� �Ÿ��� ���� 2���� ����1���� ������ �� ����. (������ �������� �������� �����̱� ����)
    system("mode con: lines=30 cols=90");
    m_ScreenWidth = 90;
    m_ScreenHeight = 30;

    // cmd���� Ŀ�� ���ڰŸ��� ���� �����ϱ� ���� �ɼ� ����
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;

    // 2���� ��ũ�����۸� �����Ͽ� �ʱ�ȭ�Ѵ�. (���� ���۸� ������ ����)
    //  [���� ���۸�]
    //    - ��ü�� �ϳ��� �׷����� ������ �ǽð����� �������� �ʰ�
    //      �� �׷��� �� �ѹ��� ǥ�õǵ��� �Ͽ� ȭ�鿡 �ܻ��̳� ������ ����
    //      ������ �ʵ��� �ϴ� �⺻���� ������ ����̴�.
    DWORD accessFlag = GENERIC_READ | GENERIC_WRITE;
    DWORD bufferFlag = CONSOLE_TEXTMODE_BUFFER;
    m_ScreenBuffer[0] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
    m_ScreenBuffer[1] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
    SetConsoleCursorInfo(m_ScreenBuffer[0], &cci);
    SetConsoleCursorInfo(m_ScreenBuffer[1], &cci);

    // 0�� ���۸� Ȱ��ȭ �ϰ�(���� ���̴� ����), ����� �ε����� 1�� �����Ѵ�.(������ �׷��� ����)
    //  [�����]
    //    - ���� ���۸����� ���� ȭ�鿡 ������� �ʴ� ����(Back Buffer)�� �ǹ��Ѵ�.
    //  [����]
    //    - ���α׷��ֿ��� ���۶�, � �۾��� �ϱ� ���� �̸� ����(�Ҵ�)�س��� �޸� ������ �ǹ��Ѵ�.
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
    // ����� ��ü�� ' '���ڷ� ä���.
    // ��, �ƹ� ���ڵ� ������ �ʰ� �����ִ� ����.
    DWORD dw;
    DWORD screenSize = m_ScreenWidth * m_ScreenHeight;
    FillConsoleOutputCharacter(m_ScreenBuffer[m_BackBufferIdx], L' ', screenSize, { 0, 0 }, &dw);
}

void Console::SwapBuffer()
{
    // ������ ����۸� ȭ�鿡 ����Ǵ� ��ũ�����۷� �����ϰ�, ����� �ε����� ��ü�Ѵ�.
    // �̸����� ���� �����ӿ��� ����ۿ� Print�� ��� ���ڵ��� ��ũ���� �������. (������)
    // ���� ���� ǥ�õǰ� �ִ� ���۴� ����۷� ��ȯ�ǰ�, ���� �����ӿ��� �ش� ���ۿ� �׸��� �ȴ�.
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_BackBufferIdx]);
    switch (m_BackBufferIdx)
    {
    case 0: m_BackBufferIdx = 1; break;
    case 1: m_BackBufferIdx = 0; break;
    }
}

void Console::Print(wchar_t _shape, short _x, short _y)
{
    // ������ ����ۿ��� Ŀ���� ������ ��ġ�� �̵���Ű��, �� ��ġ�� 1���� ���ڸ� Write�Ѵ�.
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
    WriteConsole(m_ScreenBuffer[m_BackBufferIdx], &_shape, 1, &dw, nullptr);
}

void Console::PrintText(const std::wstring& _text, short _x, short _y)
{
    // ���� ����������, 1���� ���ڰ� �ƴ� �������� ����, ��, ���ڿ��� Write�Ѵ�.
    // std::wstring���� c_str()����Լ��� �ش� ��Ʈ���� ù��° ������ �ּҸ� �����´�.
    // ��, ���� &_shape�� �����ϰ� Write�� ������ �����ּҰ� �Ѱ����� �ǰ�, �� ���� �μ���
    // _text.length()�� ���� ��ŭ�� ���̸�ŭ ���ڿ��� Write������ �˷��ִ� ��.
    // �⺻�����δ� ���� Print()�Լ��� �����ص� ������, �޴� �� �ؽ�Ʈ ������ ���ϰ� ����Ϸ���
    // �̷��� ���ڿ� ��¿� �Լ��� �����س��� ���� ����.
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
    WriteConsole(m_ScreenBuffer[m_BackBufferIdx], _text.c_str(), _text.length(), &dw, nullptr);
}

RECT Console::GetBoundaryBox() const
{
    // ���� �ܼ�â�� �����¿� ����ǥ, ��, �ٿ������ RECT�� ��� ��ȯ�Ѵ�.
    // ���� �������� ������ 1ĭ�� ���� ������ -2, -1�� ����� �߰��ȴ�.
    // ������ǥ�� -2�� ���� ������ ���ݸ�ŭ�� ���̿��� ������ ���̰� �پ����� 2�迩�� �ϱ� ����.
    RECT boundaryBox;
    boundaryBox.top = 0;
    boundaryBox.left = 0;
    boundaryBox.right = m_ScreenWidth - 2;
    boundaryBox.bottom = m_ScreenHeight - 2; // �Ʒ� ������ ���� ���� -1 �߰�(������ ���� �����ʳ��� ǥ�úҰ�)
    return boundaryBox;
}
