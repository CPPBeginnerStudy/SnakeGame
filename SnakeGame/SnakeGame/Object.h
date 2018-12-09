#pragma once
class Object
{
public:
    Object();
    virtual ~Object();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update();
    virtual void    Render();

    wchar_t         GetShape() const { return m_Shape; }
    short           GetX() const { return m_X; }
    short           GetY() const { return m_Y; }

    void            SetShape(wchar_t _shape) { m_Shape = _shape; }
    void            SetX(short _x) { m_X = _x; }
    void            SetY(short _y) { m_Y = _y; }

    // private: ������ ������ �� Ŭ���� �������� ������ �����ϱ� ������
    // protected: ������ �����Ͽ���. �� ������ �ڽ� Ŭ���������� ������ ������ �����̴�.
protected:
    // �������� ��ü�� �ڽ��� ����� �ϳ��� ����(wchar_t)�� ��Ÿ����,
    // x, y ��ǥ�� ���� ���� ��ġ�� �� �� �ְ� �Ѵ�.
    // cmd���� ���̺귯�� �Լ����� ��ǥ������ shortŸ������ �ٷ�� ������
    // ���⼭�� shortŸ������ ��ǥ������ �����Ѵ�.
    wchar_t         m_Shape;
    short           m_X;
    short           m_Y;

    // ���� �̵������� ������/���� ����, ��/�Ʒ� ���� �ϱ� ���� �����̴�.
    bool            m_IsRight;
    bool            m_IsBottom;
};
