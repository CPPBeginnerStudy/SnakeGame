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

    // ���� �� ���ڿ� ��¿��� char, string�� �ƴ� wchar_t, wstring�� ���� ������
    // �⺻ ����Ÿ�����δ� �ѱ��̳� Ư����ȣ�� ǥ���ϱ� ��Ʊ� �����̴�.
    // char�� �⺻������ 1����Ʈ���� ���� �����ѵ�, �ѱ� �� Ư����ȣ�� �ּ� 2����Ʈ�� �ʿ��ϱ� ������
    // wchar_t�� ����ؾ� �ϳ��� ���ڸ� ������ ǥ���� �� �ִ�.
    // (wchar_t�� 2����Ʈ ũ���� Ÿ���̴�.)
    // wstring�� �̷��� wchar_t�� �̿��ϴ� string�� �ٸ� �����̶�� ���� �ȴ�.
    // ���� ��� '�����ڵ�'��� ���ڵ� ����� �� wchar_t�� �̿��Ѵ�.
    // �̿� ���� �� �� �ڼ��� �˰� �ʹٸ�, MBCS(Multi Byte)�� WBCS(Wide Byte)�� ���̸� ���۸��ؼ� �����غ���.
    void    Print(wchar_t _shape, short _x, short _y);
    void    PrintText(const std::wstring& _text, short _x, short _y);

    RECT    GetBoundaryBox() const;

private:
    short   m_ScreenWidth;
    short   m_ScreenHeight;
    HANDLE  m_ScreenBuffer[2];
    short   m_BackBufferIdx;
};
