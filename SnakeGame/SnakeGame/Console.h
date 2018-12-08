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

    // 문자 및 문자열 출력에서 char, string이 아닌 wchar_t, wstring을 쓰는 이유는
    // 기본 문자타입으로는 한글이나 특수기호를 표현하기 어렵기 때문이다.
    // char는 기본적으로 1바이트만을 저장 가능한데, 한글 및 특수기호는 최소 2바이트가 필요하기 때문에
    // wchar_t를 사용해야 하나의 글자를 온전히 표현할 수 있다.
    // (wchar_t는 2바이트 크기의 타입이다.)
    // wstring은 이러한 wchar_t를 이용하는 string의 다른 버전이라고 보면 된다.
    // 흔히 듣던 '유니코드'라는 인코딩 방법이 이 wchar_t를 이용한다.
    // 이에 대해 좀 더 자세히 알고 싶다면, MBCS(Multi Byte)와 WBCS(Wide Byte)의 차이를 구글링해서 공부해보자.
    void    Print(wchar_t _shape, short _x, short _y);
    void    PrintText(const std::wstring& _text, short _x, short _y);

    RECT    GetBoundaryBox() const;

private:
    short   m_ScreenWidth;
    short   m_ScreenHeight;
    HANDLE  m_ScreenBuffer[2];
    short   m_BackBufferIdx;
};
