#include "pch.h"
#include "Console.h"


// 기본적으로 클래스의 모든 멤버변수는 생성자에서 아래와 같이 초기화해주어야 한다.
// 그렇지 않으면 값이 대입되지 않은 상태로 사용할 위험이 있고,
// 그런 경우 '쓰레기값'이라고 불리는 비정상적인 값으로 사용될 수 있기 때문이다.
Console::Console()
    : m_ScreenWidth(0)      // 첫번째 변수는 : 다음에
    , m_ScreenHeight(0)     // 다음부터는 , 다음에 쓴다.
    , m_BackBufferIdx(0)    // () 안에 초기화할 값을 넣는다.
{
    // 멤버변수가 배열인 경우 위에서 초기화 하지 않고,
    // 아래와 같이 각 배열 항목들을 직접 초기화해주어야 한다.
    // nullptr이란, 포인터변수에 대한 제로값이라고 보면 되며,
    // 아래 변수는 타입은 HANDLE 타입이지만, 실제론 어떤 객체의 포인터 타입이다.
    // 즉, HANDLE 타입은 포인터 타입.
    m_ScreenBuffer[0] = nullptr;
    m_ScreenBuffer[1] = nullptr;
}

Console::~Console()
{
}

void Console::Init()
{
    // cmd창 크기 설정 (30개의 줄(세로), 90개의 컬럼(가로))
    // cmd에서 실제 거리는 가로 2개가 세로1개와 동일한 점 참고. (문자의 가로폭이 세로폭의 절반이기 때문)
    system("mode con: lines=30 cols=90");
    m_ScreenWidth = 90;
    m_ScreenHeight = 30;

    // cmd에서 커서 깜박거리는 것을 제거하기 위한 옵션 셋팅
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;

    // 2개의 스크린버퍼를 생성하여 초기화한다. (더블 버퍼링 구현을 위해)
    //  [더블 버퍼링]
    //    - 객체가 하나씩 그려지는 과정을 실시간으로 보여주지 않고
    //      다 그려진 후 한번에 표시되도록 하여 화면에 잔상이나 깜박임 등이
    //      생기지 않도록 하는 기본적인 렌더링 기법이다.
    DWORD accessFlag = GENERIC_READ | GENERIC_WRITE;
    DWORD bufferFlag = CONSOLE_TEXTMODE_BUFFER;
    m_ScreenBuffer[0] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
    m_ScreenBuffer[1] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
    SetConsoleCursorInfo(m_ScreenBuffer[0], &cci);
    SetConsoleCursorInfo(m_ScreenBuffer[1], &cci);

    // 0번 버퍼를 활성화 하고(현재 보이는 버퍼), 백버퍼 인덱스를 1로 지정한다.(다음에 그려질 버퍼)
    //  [백버퍼]
    //    - 더블 버퍼링에서 현재 화면에 노출되지 않는 버퍼(Back Buffer)를 의미한다.
    //  [버퍼]
    //    - 프로그래밍에서 버퍼란, 어떤 작업을 하기 위해 미리 마련(할당)해놓는 메모리 공간을 의미한다.
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
    // 백버퍼 전체를 ' '문자로 채운다.
    // 즉, 아무 글자도 보이지 않게 지워주는 동작.
    DWORD dw;
    DWORD screenSize = m_ScreenWidth * m_ScreenHeight;
    FillConsoleOutputCharacter(m_ScreenBuffer[m_BackBufferIdx], L' ', screenSize, { 0, 0 }, &dw);
}

void Console::SwapBuffer()
{
    // 현재의 백버퍼를 화면에 노출되는 스크린버퍼로 지정하고, 백버퍼 인덱스를 교체한다.
    // 이를통해 현재 프레임에서 백버퍼에 Print한 모든 글자들이 스크린에 띄워진다. (렌더링)
    // 이후 원래 표시되고 있던 버퍼는 백버퍼로 전환되고, 다음 프레임에서 해당 버퍼에 그리게 된다.
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_BackBufferIdx]);
    switch (m_BackBufferIdx)
    {
    case 0: m_BackBufferIdx = 1; break;
    case 1: m_BackBufferIdx = 0; break;
    }
}

void Console::Print(wchar_t _shape, short _x, short _y)
{
    // 현재의 백버퍼에서 커서를 지정한 위치로 이동시키고, 그 위치에 1개의 글자를 Write한다.
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
    WriteConsole(m_ScreenBuffer[m_BackBufferIdx], &_shape, 1, &dw, nullptr);
}

void Console::PrintText(const std::wstring& _text, short _x, short _y)
{
    // 위와 동일하지만, 1개의 글자가 아닌 여러개의 글자, 즉, 문자열을 Write한다.
    // std::wstring에서 c_str()멤버함수는 해당 스트링의 첫번째 글자의 주소를 가져온다.
    // 즉, 위의 &_shape와 동일하게 Write할 문자의 시작주소가 넘겨지게 되고, 그 다음 인수인
    // _text.length()를 통해 얼만큼의 길이만큼 문자열을 Write할지를 알려주는 것.
    // 기본적으로는 위의 Print()함수만 구현해도 되지만, 메뉴 등 텍스트 정보를 편하게 출력하려면
    // 이러한 문자열 출력용 함수도 구현해놓는 것이 좋다.
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
    WriteConsole(m_ScreenBuffer[m_BackBufferIdx], _text.c_str(), _text.length(), &dw, nullptr);
}

RECT Console::GetBoundaryBox() const
{
    // 현재 콘솔창의 상하좌우 끝좌표, 즉, 바운더리를 RECT에 담아 반환한다.
    // 실제 보여지는 구간은 1칸씩 적기 때문에 -2, -1의 계산이 추가된다.
    // 가로좌표가 -2인 것은 세로의 절반만큼의 길이여서 동일한 길이가 줄어드려면 2배여야 하기 때문.
    RECT boundaryBox;
    boundaryBox.top = 0;
    boundaryBox.left = 0;
    boundaryBox.right = m_ScreenWidth - 2;
    boundaryBox.bottom = m_ScreenHeight - 2; // 아래 한줄을 비우기 위해 -1 추가(마지막 줄은 오른쪽끝이 표시불가)
    return boundaryBox;
}
